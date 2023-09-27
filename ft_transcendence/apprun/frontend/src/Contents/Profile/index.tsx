import React, { useState } from 'react';
import ProfileImage from '../../ProfieImage';
import { Layout, theme, Modal, Button, Input, Switch } from 'antd';
import axios from 'axios';
import { useEffect, ChangeEvent } from 'react';
import { Form } from "antd";
import { InputOTP } from "antd-input-otp"; // Don't forget to import this too!
import { useRouter } from 'next/router';
import { clientConfig } from "../../../oauth";

const { Content, Footer } = Layout;

const server_uri = clientConfig.server_uri;


interface INickCToS {
    newNick: string
}

interface IOTPUrl {
    url: string,
}

export default function ProfilePage(props) {
    axios.defaults.withCredentials = true;

    const { token: { colorBgContainer }, } = theme.useToken();

    const [profile, setProfile] = useState(null);
    const [profileUrl, setProfileUrl] = useState<string>("");
    const [isModalVisible, setIsModalVisible] = useState(false);

    const [isOTPModalVisible, setIsOTPModalVisible] = useState(false);
    const [isOTPCloseModalVisible, setIsOTPCloseModalVisible] = useState(false);

    const [newNickname, setNewNickname] = useState('');
    const [bUseOTP, setUseOTP] = useState<boolean>(false);

    const [OTPUrl, setOTPUrl] = useState<IOTPUrl>(null);

    const socket = props.socket;
    const setNickName = props.setNickName;
    const nickName = props.nickName;

    const router = useRouter();

    const fetchProfile = (): void => {
        axios.get(`${server_uri}/users/mynick`).then(response => {
            setNickName(response.data);
            axios.get(`${server_uri}/users/profile?nickname=${response.data}`).then(response => {
                console.log(response.data);
                setProfile(response.data);
                setUseOTP(response.data.bIsTFAEnabled);
                setProfileUrl(`${server_uri}/users/avatar/${response.data.avatar}`);
                axios.get(`${server_uri}/users/avatar/${response.data.avatar}`).then(avatarRp => {
                }).catch(err => { 
                    //router.push("/login"); 
                });
            }).catch(error => { 
                //router.push("/login"); 
            });
        }).catch(error => { 
            //router.push("/login");
    });

    }

    useEffect(() => {

        fetchProfile();

        return () => {
            setProfile(null);
            setProfileUrl("");
        };
    }, []);

    const onClickSetNickNameModalOK = (): void => {

        if (newNickname === "") {
            return;
        }

        const nickCToS: INickCToS = {
            newNick: newNickname
        }

        socket?.emit("nick", nickCToS);
        console.log("socket emit nick");
        console.log(nickCToS);

        setIsModalVisible(false)
    }

    const onClickSetProfileImage = async (event: ChangeEvent<HTMLInputElement>) => {
        const file = event.target.files[0];
        const formData = new FormData();
        formData.append("avatar", file);

        axios.post(`${server_uri}/users/avatar`, formData).then(response => {
            setProfileUrl(`${server_uri}/users/avatar/${response.data}?${Date.now()}`);
        }).catch(err => { });

    }

    const [form] = Form.useForm();

    const modalClean = (): void => {
        setIsModalVisible(false);
        setIsOTPCloseModalVisible(false);
        setIsOTPModalVisible(false);
    }

    const handleFinish = (values) => {
        // The value will be array of string
        // Check the field if there is no value, or value is undefined/empty string

        const { otp } = values;
        const otpNumber: string = otp?.join().replaceAll(",", "");
        console.log(`OTP: ${otpNumber}`);

        if (!otp || otp.includes(undefined) || otp.includes("")) {
            return form.setFields([
                {
                    name: "otp",
                    errors: ["OTP is invalid."]
                }
            ]);
        }

        if (!bUseOTP) {
            axios.post(`${server_uri}/auth/turn-on-2fa`, { code: otpNumber }).then(req => {
                alert("turn on");
                console.log(req);
                setUseOTP(true);
                modalClean();
                fetchProfile();
            }).catch(err => { console.log("turn on err") });
        } else {
            axios.post(`${server_uri}/auth/turn-off-2fa`, { code: otpNumber }).then(req => {
                alert("turn off");
                setUseOTP(false);
                console.log(req);
                modalClean();
            }).catch(err => { console.log("turn off err") });
        }

        //router.replace("/main");
    };

    const onClickShowModal = (): void => {
        if (bUseOTP) {
            setIsOTPCloseModalVisible(true);
        } else {
            //setOTPUrl(newOTPUrl)
            setIsOTPModalVisible(true);
        }
    }

    //이미 적용되어있다면 
    //취소하기

    return (
        <div>
            <Content style={{ margin: '24px 16px 0', overflow: 'initial' }}>
                <div style={{ padding: 12, textAlign: 'center', background: colorBgContainer }}>
                    <ProfileImage src={profileUrl} />
                </div>

                <Layout style={{ padding: 0, textAlign: 'center', background: colorBgContainer }} > {nickName} </Layout>
                <Layout style={{ padding: 12, textAlign: 'center', background: colorBgContainer }} > Rank : {profile?.rank} </Layout>

                {/* 닉네임 변경 버튼 */}
                <Layout style={{ padding: 12, textAlign: 'center', background: colorBgContainer }}>
                    <Button type="primary" onClick={() => setIsModalVisible(true)}> Change Nickname </Button>
                </Layout>

                {/* 오티피 보기 버튼 */}
                <Layout style={{ padding: 12, textAlign: 'center', background: colorBgContainer }}>
                    <Button type="primary" onClick={onClickShowModal}> {bUseOTP ? "OTP 삭제" : "OTP 생성"} </Button>
                </Layout>

                {/* 프로필 변경 버튼 */}
                {/* //<label for="profileInput">프로필 변경</label> */}
                <Layout style={{ padding: 12, textAlign: 'center', background: colorBgContainer }}>
                    <Input type="file" onChange={onClickSetProfileImage} style={{ display: 'none' }} accept=".jpg, .png" />
                    <Button type="primary" onClick={() => document.querySelector('input[type="file"]').click()}>
                        Choose Profile Image
                    </Button>
                </Layout>

                {/* 로그아웃
                <Layout style={{ padding: 12, textAlign: 'center', background: colorBgContainer }}>
                    <Button type="primary" onClick={onClickLogout}> Logout </Button>
                </Layout> */}


                {/* 닉네임 변경 모달 */}
                <Modal
                    title="Change Nickname"
                    open={isModalVisible}
                    onOk={onClickSetNickNameModalOK}
                    onCancel={() => setIsModalVisible(false)}
                >
                    <Input
                        placeholder="Enter new nickname"
                        value={newNickname}
                        onChange={(e) => setNewNickname(e.target.value)}
                    />
                </Modal>

                {/* OTP 생성 모달 */}
                <Modal
                    title="OTP"
                    open={isOTPModalVisible}
                    footer={null} // Remove OK and Cancel buttons
                    onCancel={() => setIsOTPModalVisible(false)}
                    width={400} // Set the width of the modal
                >
                    <div style={{ display: 'flex', alignItems: 'center', justifyContent: 'space-between', marginBottom: '16px' }}>
                        <span>OTP 설정</span>
                    </div>

                    <img className="phoneImage" alt="iPhone_01" src={!bUseOTP ? `${server_uri}/auth/generate-2fa?${Date.now()}` : ""} />

                    <Form form={form} onFinish={handleFinish}>

                        <Form.Item
                            name="otp"
                            className="center-error-message"
                            rules={[{ validator: async () => Promise.resolve() }]}
                        >
                            <InputOTP autoFocus inputType="numeric" length={6} />
                        </Form.Item>

                        <Form.Item noStyle>
                            <Button block htmlType="submit" type="primary">
                                적용하기
                            </Button>
                        </Form.Item>

                    </Form>
                </Modal>

                {/* OTP 삭제 모달 */}
                <Modal
                    title="OTP"
                    open={isOTPCloseModalVisible}
                    footer={null} // Remove OK and Cancel buttons
                    onCancel={() => setIsOTPCloseModalVisible(false)}
                    width={400} // Set the width of the modal
                >
                    <div style={{ display: 'flex', alignItems: 'center', justifyContent: 'space-between', marginBottom: '16px' }}>
                        <span>OTP 끄기</span>
                    </div>

                    <Form form={form} onFinish={handleFinish}>

                        <Form.Item
                            name="otp"
                            className="center-error-message"
                            rules={[{ validator: async () => Promise.resolve() }]}
                        >
                            <InputOTP autoFocus inputType="numeric" length={6} />
                        </Form.Item>

                        <Form.Item noStyle>
                            <Button block htmlType="submit" type="primary">
                                삭제하기
                            </Button>
                        </Form.Item>

                    </Form>


                </Modal>


                {/* 업적 */}
                <Layout style={{ background: colorBgContainer, overflow: 'initial' }}>

                    <h1 style={{ marginLeft: 80, background: colorBgContainer }} > Achievement </h1>

                    {profile?.achivements?.map(achievement => (
                        <div key={achievement.id} style={{ padding: 1, textAlign: 'center', background: colorBgContainer }}>
                            <h3> {achievement.achivementName} {" "} Date: {achievement.date}</h3>
                        </div>
                    ))}

                </Layout>

                {/* //매칭 히스토리 */}
                <Layout style={{ background: colorBgContainer, overflow: 'initial' }}>
                    <h1 style={{ marginLeft: 80, background: colorBgContainer }} > History </h1>

                    {profile?.matchRecords?.map((history, index) => (
                        <div key={index} style={{ padding: 1, textAlign: 'center', background: colorBgContainer }}>
                            <h3> Type: {history?.matchType} Winner: {history?.winner} Score: {history?.player1Score} {" "} {history?.player2Score} {" "} Date: {history.date}</h3>
                        </div>
                    ))}
                </Layout>


            </Content>

            <Footer style={{ textAlign: 'center' }}>Transcendence ©2023 Created by 42 students</Footer>

        </div>
    )
}
