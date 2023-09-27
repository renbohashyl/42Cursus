import React, { useState } from "react";
import { Modal, Button, Input, List, Typography, Checkbox, Form } from "antd";
import { LockOutlined, PlusOutlined } from "@ant-design/icons";

import {    
    IChatCreateCToS,
    IChatJoinCToS,
    IChannelInfo,
} from "../Interface";


interface IPropsChannelList {
    socket: any;
    channels: IChannelInfo[];
    addChannel: any;
}

const ChannelListPage: React.FC<IPropsChannelList> = (props) => {
    const { socket, channels, addChannel } = props;

    const [createModalVisible, setCreateModalVisible] = useState<boolean>(false);
    const [accessModalVisible, setAccessModalVisible] = useState<boolean>(false);

    const [selectedChannel, setSelectedChannel] = useState<any | null>(null); // Update the type here
    const [isPasswordProtectedChannel, setIsPasswordProtectedChannel] = useState<boolean>(false);
    const [password, setPassword] = useState<string>("");

    const [newChannelName, setNewChannelName] = useState<string>("");
    const [isPasswordProtected, setIsPasswordProtected] = useState<boolean>(false);
    const [newChannelPassword, setNewChannelPassword] = useState<string>("");

    const onTurnOffCreateChannelModal = (): void => {
        setCreateModalVisible(false);
        setIsPasswordProtected(false);
        setNewChannelName("");
        setNewChannelPassword("");
    }

    const onClickChannel = (channel: any): void => {
        setSelectedChannel(channel);
        setIsPasswordProtectedChannel(channel.isProtected);
        setAccessModalVisible(true);
    };

    const onClickChannelAccessModalYes = (): void => {

        const joinInfo: IChatJoinCToS = {
            roomID: selectedChannel.roomID,
            password: password,
        }

        socket?.emit("join", joinInfo);        
        console.log("socket emit join");
        console.log(joinInfo);        

        setSelectedChannel(null);
        setIsPasswordProtectedChannel(false);
        setAccessModalVisible(false);
        setPassword("");
    };

    const onClickChannelAccessModalNo = (): void => {
        setSelectedChannel(null);
        setIsPasswordProtectedChannel(false);
        setAccessModalVisible(false);
    };

    const onClickCreateChannel = (): void => {
        setCreateModalVisible(true);
    };

    const onClickCreateChannelModalYes = (): void => {

        const createInfo: IChatCreateCToS = {
            name: newChannelName,
            isProtected: isPasswordProtected,
            password: newChannelPassword,
        }

        socket?.emit("create", createInfo);
        console.log("socket emit create");
        console.log(createInfo);

        onTurnOffCreateChannelModal();
    };

    const onClickCreateChannelModalNo = (): void => {
        onTurnOffCreateChannelModal();
    };

    const onCreateManyRoom = (): void => {

        for (var i = 0; i < 30; ++i) {
            const createInfo: IChatCreateCToS = {
                name: "a" + i,
                isProtected: isPasswordProtected,
                password: newChannelPassword,
            }
    
            socket?.emit("create", createInfo);
            console.log("socket emit create");
            console.log(createInfo);    
        }
        
        onTurnOffCreateChannelModal();
    }
    
    return (
        <div style={{ padding: "20px" }}>
            <List
                itemLayout="horizontal"
                dataSource={channels} // Access the channels array correctly
                renderItem={(channel: IChannelInfo) => (
                    (<List.Item
                        onClick={() => onClickChannel(channel)}
                        style={{
                            border: "1px solid #ccc",
                            marginBottom: "10px",
                            backgroundColor: selectedChannel === channel ? "rgba(0, 0, 0, 0.1)" : "transparent",
                            padding: "10px",
                            display: "flex",
                            alignItems: "center",
                        }}
                    >
                        <Typography.Text>{channel.name}</Typography.Text>
                        {channel.isProtected && <LockOutlined style={{ marginRight: "5px" }} />}
                    </List.Item>)
                )}
            />

            <Button
                type="primary"
                icon={<PlusOutlined />}
                style={{ marginTop: "10px" }}
                onClick={onClickCreateChannel}
            >
                채널 추가
            </Button>

            <Modal
                title={selectedChannel?.name}
                open={accessModalVisible}
                onCancel={onClickChannelAccessModalNo}
                footer={[
                    <Button key="no" onClick={onClickChannelAccessModalNo}>
                        아니오
                    </Button>,
                    <Button key="yes" type="primary" onClick={onClickChannelAccessModalYes}>
                        네
                    </Button>,
                ]}
            >
                정말 이 방에 접속하시겠습니까?
                {isPasswordProtectedChannel && (
                    <Input.Password
                        value={password}
                        onChange={(e) => setPassword(e.target.value)}
                        placeholder="비밀번호를 입력하세요"
                    />
                )}

            </Modal>

            <Modal
                title="채널 만들기"
                open={createModalVisible}
                onCancel={onClickCreateChannelModalNo}
                onOk={onClickCreateChannelModalYes}
            >
                <Form>
                    <Form.Item label="Channel Name">
                        <Input value={newChannelName} onChange={(e) => setNewChannelName(e.target.value)} />
                    </Form.Item>

                    <Form.Item label="Password Protected">
                        <Checkbox checked={isPasswordProtected} onChange={(e) => setIsPasswordProtected(e.target.checked)} />
                    </Form.Item>

                    {isPasswordProtected && (
                        <Form.Item label="Password">
                            <Input.Password
                                value={newChannelPassword}
                                onChange={(e) => setNewChannelPassword(e.target.value)}
                                placeholder="비밀번호를 입력하세요"
                            />
                        </Form.Item>
                    )}
                </Form>
            </Modal>
        </div>
    );
};

export default ChannelListPage;
