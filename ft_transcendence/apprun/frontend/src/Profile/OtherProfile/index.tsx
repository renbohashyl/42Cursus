import React, { useEffect, useState } from 'react';
import { Layout, theme, Button } from 'antd';
import axios from 'axios';
import { clientConfig } from '../../../oauth';
import ProfileImage from '../../ProfieImage';
import { IFriendInfo } from '../../Contents/Chat/Interface';
import { IUnFriendSToC } from '../../Contents/Chat/Interface';

const { Content, Footer } = Layout;

interface IBlockCToS {
    nick: string
}

interface IUnBlockCToS {
    nick: string
}

const server_uri = clientConfig.server_uri;

export default function ShowUserProfilePage(props) {
    const { colorBgContainer } = theme.useToken();


    console.log(`userName: ${props.userName} nickNamee: ${props.nickName}`)

    const socket = props.socket;
    const friends: IFriendInfo[] = props.friends;
    const blockList: string[] = props.blockList;

    const isFriend = (friendName: string): boolean => {
        const findFriend: IFriendInfo = friends?.find((friendInfo: IFriendInfo) => friendInfo.nick === friendName);
        if (findFriend != undefined) {
            return true;
        }
        return false;
    }

    const isBlock = (usrName: string): boolean => {
        const blockName: string = blockList?.find((blockName: string) => blockName === usrName);
        if (blockName == usrName) {
            return true;
        }
        return false;
    }

    const [profile, setProfile] = useState(null);
    const [profileUrl, setProfileUrl] = useState<string>("");

    useEffect(() => {
        axios.get(`${server_uri}/users/profile?nickname=${props.userName}`)
            .then(response => {                
                console.log(response.data);
                setProfile(response.data);
                setProfileUrl(`${server_uri}/users/avatar/${response.data.avatar}`);
            }).catch(error => { });
    }, [props?.userName])


    //Frined
    const onClickAddFriendModalYes = () => {
        socket?.emit("friend", { nick: props.userName });
        console.log("socket emit friend");
        console.log({ nick: props.userName });
    };

    const onClickRemoveFriendModalYes = () => {
        const unfriendCToS: IUnFriendSToC = {
            nick: props.userName
        }

        socket?.emit("unfriend", unfriendCToS);
        console.log("socket emit unfriend");
        console.log(unfriendCToS);
    };

    //Block   
    const onClickBlockUserModalOK = () => {

        const blockUser: IBlockCToS = {
            nick: props.userName
        }

        socket?.emit("block", blockUser);
        console.log("socket emit block");
        console.log(blockUser);
    };

    const onUnblockUserConfirm = () => {
        console.log("unblock!");
        const unBlockUser: IUnBlockCToS = {
            nick: props.userName
        }

        socket?.emit("unblock", unBlockUser);
        console.log("socket emit unblock");
        console.log(unBlockUser);
    };



    return (
        <div>
            <Content style={{ margin: '24px 16px 0', overflow: 'initial' }}>
                {profile && (
                    <>
                        <div style={{ padding: 12, textAlign: 'center', background: colorBgContainer }}>
                            {/* Profile Image */}
                            <ProfileImage src={profileUrl} />
                        </div>

                        <Layout style={{ padding: 0, textAlign: 'center', background: colorBgContainer }}>
                            {/* Nickname */}
                            {props.userName}
                        </Layout>

                        <Layout style={{ padding: 12, textAlign: 'center', background: colorBgContainer }}>
                            {/* Rank */}
                            Rank: {profile?.rank}
                        </Layout>



                        {(props?.userName != props?.nickName) && (
                            <div>
                                {/* frined */}
                                <Layout style={{ padding: 12, textAlign: 'center', background: colorBgContainer }}>
                                    <Button onClick={isFriend(props.userName) ? onClickRemoveFriendModalYes : onClickAddFriendModalYes}> {isFriend(props.userName) ? "Remove Friend" : "Add Friend"}  </Button>
                                </Layout>

                                {/* block */}
                                <Layout style={{ padding: 12, textAlign: 'center', background: colorBgContainer }}>
                                    <Button onClick={isBlock(props.userName) ? onUnblockUserConfirm : onClickBlockUserModalOK}> {isBlock(props.userName) ? "UnBlock" : "Add Block"}  </Button>
                                </Layout>
                            </div>
                        )}



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
                    </>
                )}
            </Content>            
        </div>
    );
}
