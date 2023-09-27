import React, { useState } from 'react';
import { Layout, theme, Button } from 'antd';
import axios from 'axios';
import ProfileImage from '../../../ProfieImage';

import { clientConfig } from '../../../../oauth';

import { IFriendInfo } from '../../Chat/Interface';
import ShowUserProfilePage from '../../../Profile/OtherProfile';

const { Content, Footer } = Layout;

import { IUnFriendSToC } from '../../Chat/Interface';

const server_uri = clientConfig.server_uri;

export default function UserProfilePage(props) {
    const { colorBgContainer } = theme.useToken();
    const [searchQuery, setSearchQuery] = useState('');
    const [profile, setProfile] = useState(null);
    const [userNickName, setUserNickName] = useState("NULL");
    //const [bFriend, setIsFriend] = useState<boolean>(false);

    const socket = props.socket;
    const myNickName = props.nickName;
    const friends: IFriendInfo[] = props.friends;

    const isFriend = (friendName: string): boolean => {
        const findFriend: IFriendInfo = friends?.find((friendInfo: IFriendInfo) => friendInfo.nick === friendName);
        if (findFriend != undefined) {
            return true;
        }
        return false;
    }

    const [profileUrl, setProfileUrl] = useState<string>("");

    const onClickSearchButton = () => {

        if (searchQuery.trim() === '') {
            return;
        }

        axios.get(`${server_uri}/users/profile?nickname=${searchQuery}`)
            .then(response => {
                setUserNickName(searchQuery);
                setProfile(response.data);
                setProfileUrl(`${server_uri}/users/avatar/${response.data.avatar}`);
            }).catch(error => { });
    };

    const onClickAddFriendModalYes = () => {
        socket?.emit("friend", { nick: searchQuery });
        console.log("socket emit friend");
        console.log({ nick: searchQuery });
    };

    const onClickRemoveFriendModalYes = () => {
        const unfriendCToS: IUnFriendSToC = {
            nick: searchQuery
        }

        socket?.emit("unfriend", unfriendCToS);
        console.log("socket emit unfriend");
        console.log(unfriendCToS);
    };

    const onChangeQuery = (nickName: string): void => {
        setSearchQuery(nickName);
        setProfile(null);
    }


    return (
        <div>
            <Content style={{ margin: '24px 16px 0', overflow: 'initial' }}>
                <div style={{ padding: 12, textAlign: 'center', background: colorBgContainer }}>
                    {/* Search Input */}
                    <input
                        type="text"
                        onChange={e => onChangeQuery(e.target.value)}
                        placeholder="Enter user nickname"
                    />
                    <button onClick={onClickSearchButton}>Search</button>
                </div>

                {profile && (
                    <>
                       <ShowUserProfilePage socket={props?.socket} userName={userNickName} friends={props?.friends} blockList={props?.blockList} nickName={props?.nickName}/>
                    </>
                )}
            </Content>

            <Footer style={{ textAlign: 'center' }}>Transcendence ©2023 Created by 42 students</Footer>
        </div>
    );
}
