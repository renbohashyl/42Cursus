import { useEffect } from "react";
import axios from 'axios';
import { io } from "socket.io-client";
import type { MenuProps } from 'antd';
import { Layout, Menu, theme } from 'antd';
import React, { useState } from "react";
import ProfilePage from "../../src/Contents/Profile";
import GamePage from "../../src/Contents/Game";

import ChatPage from "../../src/Contents/Chat/Chat";
import DMPage from "../../src/Contents/Chat/DM";
import ChannelListPage from "../../src/Contents/Chat/Channels";
import FriendListPage from "../../src/Contents/Chat/Friends";
import BlockListPage from "../../src/Contents/Chat/Block";
import UserProfilePag from "../../src/Contents/Profile/Other";

import { Button, notification, Space } from 'antd';

import { clientConfig } from "../../oauth";
const server_uri = clientConfig.server_uri;

import { Modal, Input, Switch } from 'antd';
import { Form } from "antd";

//interface
import {
    IBlocksSToC,
    IDMSToC,
    IFriendInfo,
    IDMInfo,
    IChansSToC,
    IChannelInfo,
    IUsersSToC,
    IJoinCToS,
    IJoinSToC,
    IChatAdminCToS,
    ICloseSToC,
    IMuteSToC,
    IUnMuteSToC,
    IChatLeavCToS,
    IAdminSToC,
    IPublicSToC,
    IPrivateSToC,
    IProtectSToC,
    IMsgSToC,
    IKickSToC,
    IBanSToC,
    IBlockSToC,
    IUnBlockSToC,
    IFriendSToC,
    IUnFriendSToC,
    IRejectSToC,
    IUserInfo,
    ILeaveSToC as ILeaveSToC,
    INickSToC,
    IStateSToC,
    IFriendsSToC,
    IOpenSToC,
    IBlockedUser,
} from "../../src/Contents/Chat/Interface";

import {
    IChallengeStoC,
    IMatchedSToC,
    IVector,
    IUpdateSToC,
    IScoreSToC,

} from "../../src/Contents/Game/Interface";

import {
    AppstoreOutlined,
    BarChartOutlined,
    CloudOutlined,
    ShopOutlined,
    TeamOutlined,
    UploadOutlined,
    UserOutlined,
    VideoCameraOutlined,
    MailOutlined,
    SettingOutlined
} from '@ant-design/icons'
import { rejects } from "assert";
import { useResolvedPath } from "react-router-dom";
import { useRouter } from "next/router";

const { Header, Content, Footer, Sider } = Layout;

interface ITakeCToS {
    ftLogin: string
}

interface IRefuseCToS {
    ftLogin: string
}

interface IFinNoti {
    message: string
}

const items: MenuProps['items'] = [
    UserOutlined,
    VideoCameraOutlined,
    UploadOutlined,
    BarChartOutlined,
    CloudOutlined,
    AppstoreOutlined,
    TeamOutlined,
    ShopOutlined,
].map((icon, index) => ({
    key: String(index + 1),
    icon: React.createElement(icon),
    label: `nav ${index + 1}`,
}));

function getItem(label, key, icon, children) {
    return {
        key,
        icon,
        children,
        label,
    };
}

const itemses = [
    getItem('Profile', 'sub1', <MailOutlined />, [getItem('My Profile', '1'), getItem('Ohter Profile', '8')]),
    getItem('Game', 'sub2', <AppstoreOutlined />, [getItem('Ping pong', '2')]),
    getItem('Chat', 'sub4', <SettingOutlined />, [getItem('Chat', '3'), getItem('DM', '4'), getItem('Channels', '5'), getItem('Friends', '6'), getItem('block', '7'),])
];

interface IMessage {
    id: number;
    text: string;
    isUser: boolean;
    isSystem: boolean,
    from: string;
}

export default function HomePage() {
    axios.defaults.withCredentials = true;

    //=========================================================================================================================================================
    //초기화
    const [socket, setSocket] = useState(null)
    const { token: { colorBgContainer }, } = theme.useToken();
    const [selectContentNum, setContentSelectNum] = useState<string>("1");
    const [nickName, setNickName] = useState<string>("name");
    const [isShowRejectMsg, setIsShowRejectMsg] = useState<boolean>(false);
    const [bMenuMount, setMenuMount] = useState(false);
    const [rejectMessage, setRejectMessage] = useState<IRejectSToC>(null);



    //Notification

    //초기화
    //=========================================================================================================================================================    
    const onClickProfile = (event) => {
        setContentSelectNum(event.key);
    }
    //=========================================================================================================================================================

    //=========================================================================================================================================================
    //Channel List 상태        
    const [listUpChannels, setListUpChannels] = useState<IChannelInfo[]>([]); //{ roomID: 1, isProtected: false, name: "General" },
    //Channel List 상태
    //=========================================================================================================================================================



    //=========================================================================================================================================================
    //DM 상태
    const [DMessages, setDMessages] = useState<IDMInfo[]>([]);
    //DM 상태
    //=========================================================================================================================================================



    //=========================================================================================================================================================
    //채팅 상태
    const [accessChannels, setAccessChannels] = useState<IChannelInfo[]>([]); // { roomID: 1, isProtected: false, name: "General" },
    const [accessChannelsMessages, setAccessChannelsMessages] = useState<{ [channelId: number]: IMessage[] }>({});
    const [selectedAccessChannel, setSelectedAccessChannel] = useState<IChannelInfo | null>(null);
    const [accessChannelsUsersArray, setAccessChannelsUsersArray] = useState<IUsersSToC[]>([]); //{ roomID: 1, ownerOrNull: "null", users: [{ nick: "UserA", isAdmin: false, isMuted: false }, { nick: "UserB", isAdmin: false, isMuted: false }, { nick: "UserC", isAdmin: false, isMuted: false }] },
    //채팅 상태
    //=========================================================================================================================================================
    const addUserMessageInAccessChannel = (chatMessageStoC: IMsgSToC, myNickName: string) => {

        if (chatMessageStoC.message === "")
            return;

        let selectChannelName = "NULL";

        setSelectedAccessChannel(prevSelectedChannel => {
            selectChannelName = prevSelectedChannel?.name;
            return prevSelectedChannel;
        })

        const newMessage: IMessage = {
            id: Date.now(),
            text: chatMessageStoC.message,
            isUser: myNickName === chatMessageStoC?.nick,
            isSystem: false,
            from: myNickName === chatMessageStoC?.nick ? selectChannelName : chatMessageStoC?.nick,
        };

        setAccessChannelsMessages((prevMessages) => {
            const roomID = chatMessageStoC?.roomID;
            const existingMessages = prevMessages[roomID] || []; // Use an empty array if messages are undefined

            return { ...prevMessages, [roomID]: [...existingMessages, newMessage], };
        });

    };

    const onClickChannel = (channel: IChannelInfo) => {
        setSelectedAccessChannel(channel);
        if (!accessChannelsMessages[channel?.roomID]) {
            setAccessChannelsMessages((prevMessages) => ({ ...prevMessages, [channel?.roomID]: [] }));
        }
    };
    //=========================================================================================================================================================



    //=========================================================================================================================================================
    //Friend List 상태
    const [friends, setFriends] = useState<IFriendInfo[]>([]);

    //Friend List 상태
    //=========================================================================================================================================================
    const removeFriend = (friendName: string) => {
        setFriends((prevFriends: IFriendInfo[]) => {
            const newFriends = prevFriends.filter((friendInfo: IFriendInfo) => friendInfo.nick !== friendName);
            return [...newFriends];
        })
    }

    const addFriend = (friendName: string, state: string) => {
        setFriends((prevFriends: IFriendInfo[]) => {

            const friendInfo: IFriendInfo = {
                nick: friendName,
                status: state
            }

            const newFriends = prevFriends.filter((friendInfo: IFriendInfo) => friendInfo.nick !== friendName);
            return [...newFriends, friendInfo];
        })
    }

    const isFriend = (friendName: string): boolean => {

        let bFriend: boolean = false;
        setFriends((prevFriends: IFriendInfo[]) => {
            const newFriends = prevFriends.find((friendInfo: IFriendInfo) => friendInfo.nick === friendName);
            bFriend = (newFriends?.nick === friendName);
            return prevFriends;
        })

        return bFriend;
    }
    //=========================================================================================================================================================



    //=========================================================================================================================================================
    //Block List 상태
    const [blockList, setBlockList] = useState<string[]>([]);
    //Block List 상태
    //=========================================================================================================================================================
    const addBlockUser = (blockUserNick: string) => {

        setBlockList((prevBlockUsers: string[]) => {
            return [...prevBlockUsers, blockUserNick];

        });
    }

    const removeBlockedUser = (blockUserNick: string) => {
        setBlockList((prevBlockedUsers: string[]) => {
            const newBlockedUsers = prevBlockedUsers.filter((name: string) => name !== blockUserNick);
            return [...newBlockedUsers];
        })
    }

    const isBlocked = (userNickName: string) => {
        let bBlocked: boolean = false;

        setBlockList((prevBlockedUsers) => {
            const findUserNikName: string = prevBlockedUsers.find((name: string) => name === userNickName);
            bBlocked = (findUserNikName === userNickName);
            return prevBlockedUsers;
        })

        return bBlocked;
    }
    //=========================================================================================================================================================

    //=========================================================================================================================================================
    //기능
    const removeUsersSToC = (roomID: number): void => {
        setAccessChannelsUsersArray(prevUserStoCArray => {
            const newUserSToCArray: IUsersSToC[] = prevUserStoCArray.filter((prevUsers: IUsersSToC) => prevUsers?.roomID !== roomID);
            return [...newUserSToCArray];
        })
    }

    const removeUser = (targetNickName: string, targetRoomID: number): void => {
        setAccessChannelsUsersArray(prevUserStoCArray => {
            const findUserSToC: IUsersSToC = prevUserStoCArray.find((userSToC: IUsersSToC) => userSToC?.roomID === targetRoomID);
            const newUserSToCArray: IUsersSToC[] = prevUserStoCArray.filter((prevUsers: IUsersSToC) => prevUsers?.roomID !== targetRoomID);

            const newUserInfoArray: IUserInfo[] = findUserSToC?.users.filter((users: IUserInfo) => users.nick !== targetNickName);
            if (findUserSToC != undefined) {
                findUserSToC.users = newUserInfoArray;

                //오너인지체크
                if (findUserSToC.ownerOrNull === targetNickName) {
                    findUserSToC.ownerOrNull = null;
                }
            }
            return [...newUserSToCArray, findUserSToC];
        })
    }

    const removeAccessChannel = (roomID: number) => {
        setAccessChannels(prevAccessChannels => {
            const newChannels: IChannelInfo[] = prevAccessChannels.filter((channel: IChannelInfo) => channel.roomID !== roomID);
            return [...newChannels];
        });

        setSelectedAccessChannel(null);
    }

    const removeChannelInListUpChannel = (targetRoomID: number): void => {
        setListUpChannels(prevListChannels => {
            const newChannels: IChannelInfo[] = prevListChannels.filter((channel: IChannelInfo) => channel.roomID !== targetRoomID);
            return [...newChannels];
        });
    }

    const removeMessages = (roomID: number): void => {
        setAccessChannelsMessages((prevMessages) => {
            const updatedMessages = { ...prevMessages };
            delete updatedMessages[roomID];
            return updatedMessages;
        });
    }

    const addUserInAccessChannel = (roomID: number, userNickName: string): void => {
        setAccessChannelsUsersArray(prevUsersArray => {
            const findUsersSToC: IUsersSToC = prevUsersArray.find((prevUsers: IUsersSToC) => prevUsers?.roomID === roomID);
            const newUsersSToCArray: IUsersSToC[] = prevUsersArray.filter((prevUsers: IUsersSToC) => prevUsers?.roomID !== roomID);

            //오너가 아닐때
            if (findUsersSToC?.ownerOrNull !== userNickName) {
                const newUserInfo: IUserInfo = {
                    nick: userNickName,
                    isAdmin: false,
                    isMuted: false,
                }

                //중복제거
                const newUserInfos: IUserInfo[] = findUsersSToC?.users.filter((prevUserInfo: IUserInfo) => prevUserInfo.nick !== newUserInfo.nick);

                const newUsersSToC: IUsersSToC = {
                    roomID: findUsersSToC.roomID,
                    ownerOrNull: findUsersSToC.ownerOrNull,
                    users: [...newUserInfos, newUserInfo]
                };

                return [...newUsersSToCArray, newUsersSToC];
            }

            //조인 한사람이 오너일때 users에 있으므로 아무것도안함
            return [...prevUsersArray];
        })
    }

    const addAccessChannel = (roomID: number, name: string): void => {
        let channelListUp: IChannelInfo[] = [];

        setListUpChannels((prevListChannels: IChannelInfo[]) => {
            channelListUp = prevListChannels;
            return channelListUp;
        });

        setAccessChannels((prevAccessChannels: IChannelInfo[]) => {
            const findAccessChannel: IChannelInfo = channelListUp.find((channel: IChannelInfo) => channel.roomID === roomID);
            const newAccessChannels: IChannelInfo[] = prevAccessChannels.filter((channel: IChannelInfo) => channel.roomID !== roomID);

            //리스트채널에 있을때
            if (findAccessChannel != undefined) {
                const newAccessChannel: IChannelInfo = {
                    roomID: findAccessChannel.roomID,
                    isProtected: findAccessChannel.isProtected,
                    name: findAccessChannel.name,
                }
                return [...newAccessChannels, newAccessChannel];
            }

            //리스트채널에 없을때 그냥 접근시킴
            const newAccessChannel: IChannelInfo = {
                roomID: roomID,
                isProtected: false,
                name: name,
            }
            return [...newAccessChannels, newAccessChannel];
        });
    }
    //기능
    //=========================================================================================================================================================



    //=========================================================================================================================================================
    //Socket On

    const addChatSystemMessage = (roomID: number, message: string): void => {
        const newMessage: IMessage = {
            id: Date.now(),
            text: message,
            isUser: false,
            isSystem: true,
            from: "System"
        };

        setAccessChannelsMessages((prevMessages) => {
            const existingMessages = prevMessages[roomID] || [];
            return { ...prevMessages, [roomID]: [...existingMessages, newMessage], };
        });
    }

    const addDMSystemMessage = (message: string): void => {

        const DMMessage: IDMInfo = {
            id: Date.now(),
            isUser: false,
            isSystem: true,
            message: message,
            from: "",
            to: "",
        }

        setDMessages((prevDMSocketMessage) => [...prevDMSocketMessage, DMMessage]);
    }

    const changeNickName = (origin: string, to: string, myNickName: string): void => {
        console.log(`origin ${origin} myNickName ${myNickName}`);

        if (origin == myNickName) {
            setNickName(to);
        }

        setAccessChannelsUsersArray((prevUsersArray: IUsersSToC[]) => {
            const newAccessChannelUSersArray: IUsersSToC[] = prevUsersArray.map((usersSToC: IUsersSToC) => {

                const newUsers: IUserInfo[] = usersSToC.users.map((prevUser: IUserInfo) => {
                    if (origin == prevUser.nick) {
                        prevUser.nick = to;
                    }
                    return prevUser;
                })

                const newUserSToC: IUsersSToC = {
                    roomID: usersSToC.roomID,
                    ownerOrNull: usersSToC.ownerOrNull === origin ? to : usersSToC.ownerOrNull,
                    users: newUsers,
                };
                return newUserSToC;
            })

            return [...newAccessChannelUSersArray];
        })

        setFriends((prevFriends: IFriendInfo[]) => {
            const newFriends: IFriendInfo[] = prevFriends.map((friend: IFriendInfo) => {
                if (origin === friend.nick) {
                    friend.nick = to;
                }
                return friend;
            })
            return [...newFriends];
        })

        setBlockList((prevBlockUsers: string[]) => {
            const newBlockUsers: string[] = prevBlockUsers.map((blockUserName: string) => {
                if (origin === blockUserName) {
                    blockUserName = to;
                }
                return blockUserName;
            })

            return [...newBlockUsers];
        })
    }

    const leaveChannel = (myNickName: string, leaveNickName: string, roomID: number, message: string) => {
        if (myNickName == leaveNickName) {
            removeMessages(roomID);
            removeAccessChannel(roomID);
            removeUsersSToC(roomID);
        }
        else {
            removeUser(leaveNickName, roomID);
            addChatSystemMessage(roomID, message);
        }
    }

    const setChannelState = (roomID: number, state: boolean): void => {
        setListUpChannels(prevListChannels => {
            const newChannels: IChannelInfo[] = prevListChannels.filter((channel: IChannelInfo) => channel.roomID !== roomID);
            const findChannel: IChannelInfo = prevListChannels.find((channel: IChannelInfo) => channel.roomID === roomID);

            //해당채널이 리스트에 있을때
            if (findChannel != undefined) {
                findChannel.isProtected = state;
                return [...newChannels, findChannel];
            }

            //해당채널이 리스트에 없을때. 어차피 open이 날라오므로 아무것도 추가안한다. 
            return [...prevListChannels];
        });
    }

    //=========================================================================================================================================================
    //Chatting
    const onChans = (chansReq: IChansSToC): void => {
        console.log(`socket on chans`);
        console.log(chansReq);

        setListUpChannels([...chansReq.chans]);
    }

    const onBlocks = (blocksReq: IBlocksSToC): void => {
        console.log(`socket on blocks`);
        console.log(blocksReq);

        setBlockList([...blocksReq.blocks]);
    }

    const onFriends = (friendsReq: IFriendsSToC): void => {
        console.log(`socket on friends`);
        console.log(friendsReq);

        setFriends([...friendsReq.friends]);
    }

    const onState = (stateReq: IStateSToC): void => {
        console.log(`socket on state`);
        console.log(stateReq);

        setFriends((prevFriends: IFriendInfo[]) => {
            const newFriends = prevFriends.filter((friendInfo: IFriendInfo) => friendInfo.nick !== stateReq.nick);

            const friend: IFriendInfo = {
                nick: stateReq.nick,
                status: stateReq.status
            }

            return [...newFriends, friend];
        })
    }

    const onNick = (nickReq: INickSToC, myNickName: string): void => {
        console.log(`socket on nick`);
        console.log(nickReq);

        changeNickName(nickReq.oldNick, nickReq.newNick, myNickName);
    }

    const onOpen = (openChannel: IOpenSToC): void => {
        console.log(`socket on open`);
        console.log(openChannel);

        const newChannelInfo: IChannelInfo = {
            roomID: openChannel.roomID,
            isProtected: openChannel.isProtected,
            name: openChannel.name,
        }

        setListUpChannels((prevListUpChannels: IChannelInfo[]) => {
            const newListUpChannel: IChannelInfo[] = prevListUpChannels.filter((chInfo: IChannelInfo) => chInfo.roomID !== openChannel.roomID);
            return [...newListUpChannel, newChannelInfo]
        });
    }

    const onClose = (closeReq: ICloseSToC): void => {
        console.log(`socket on close`);
        console.log(closeReq);

        removeChannelInListUpChannel(closeReq.roomID);
    }

    const onJoin = (joinRoom: IJoinSToC, myNickName: string): void => {
        console.log(`socket on join`);
        console.log(joinRoom);
        console.log(`myNickName ${myNickName}`);

        addChatSystemMessage(joinRoom.roomID, `${joinRoom.nick} 님이 접속하셨습니다.`);

        if (joinRoom.nick == myNickName) {
            addAccessChannel(joinRoom.roomID, joinRoom.name);
        }
        else {
            addUserInAccessChannel(joinRoom.roomID, joinRoom.nick);
        }
    }

    const onUsers = (channelUsers: IUsersSToC): void => {
        console.log(`socket on users`);
        console.log(channelUsers);

        setAccessChannelsUsersArray(prevUsersArray => {
            const findUsers: IUsersSToC = prevUsersArray?.find((prevUsers) => prevUsers?.roomID === channelUsers?.roomID);
            const newUsersArray: IUsersSToC[] = prevUsersArray?.filter((prevUsers) => prevUsers?.roomID !== channelUsers?.roomID);

            if (findUsers == null) {
                return [...prevUsersArray, channelUsers];
            }
            else {
                return [...newUsersArray, channelUsers];
            }
        });
    }

    const onAdmin = (adminReq: IAdminSToC): void => {
        console.log("socket on admin");
        console.log(adminReq);

        setAccessChannelsUsersArray(prevUsersArray => {
            const newUsersStoCArray: IUsersSToC[] = prevUsersArray?.filter((prevUsers) => prevUsers?.roomID !== adminReq?.roomID);
            const findUsersStoC: IUsersSToC = prevUsersArray?.find((prevUsers) => prevUsers?.roomID === adminReq?.roomID);

            //유저를찾는다.
            const prevUserInfos: IUserInfo[] = findUsersStoC.users;
            const newUserInfos: IUserInfo[] = prevUserInfos?.filter((prevUser: IUserInfo) => prevUser.nick !== adminReq?.nick);
            const findUserInfo: IUserInfo = prevUserInfos?.find((prevUser: IUserInfo) => prevUser.nick === adminReq?.nick);

            findUserInfo.isAdmin = true;
            findUsersStoC.users = [...newUserInfos, findUserInfo]
            return [...newUsersStoCArray, findUsersStoC];
        });

        addChatSystemMessage(adminReq.roomID, `${adminReq.nick} 님이 admin 으로 승급!`);
    }

    const onLeave = (leaveReq: ILeaveSToC, myNickName: string): void => {
        console.log("socket on leave");
        console.log(leaveReq);

        leaveChannel(myNickName, leaveReq.nick, leaveReq.roomID, `${leaveReq.nick} 님이 채팅방에서 떠나셨습니다.`);
    }

    const onKick = (kickReq: IKickSToC, myNickName: string): void => {
        console.log("socket on kick");
        console.log(kickReq);

        leaveChannel(myNickName, kickReq.nick, kickReq.roomID, `${kickReq.nick} 님을 Kick 했습니다.`);
    }

    const onBan = (banReq: IBanSToC, myNickName: string): void => {
        console.log("socket on ban");
        console.log(banReq);

        leaveChannel(myNickName, banReq.nick, banReq.roomID, `${banReq.nick} 님을 Ban 했습니다.`);
    }

    const onMute = (muteReq: IMuteSToC): void => {
        console.log("socket on mute");
        console.log(muteReq);

        addChatSystemMessage(muteReq.roomID, `${muteReq.nick} 님이 일정시간동안 mute 상태입니다...`);
    }

    const onUnMute = (unMuteReq: IUnMuteSToC): void => {
        console.log("socket on unmute");
        console.log(unMuteReq);

        addChatSystemMessage(unMuteReq.roomID, `${unMuteReq.nick} 님은 이제 unmute 입니다.`);
    }

    const onPublic = (publicReq: IPublicSToC): void => {
        console.log("socket on public");
        console.log(publicReq);

        setChannelState(publicReq.roomID, false);
        addChatSystemMessage(publicReq.roomID, `채널이 public 으로 변경되었습니다.`);
    }

    const onPrivate = (privateReq: IPrivateSToC): void => {
        console.log("socket on private");
        console.log(privateReq);

        setListUpChannels(prevListChannels => {
            //아무튼 리스트에서 제거함
            const newChannels: IChannelInfo[] = prevListChannels.filter((channel: IChannelInfo) => channel.roomID !== privateReq.roomID);
            return [...newChannels];
        });

        addChatSystemMessage(privateReq.roomID, `채널이 private 으로 변경되었습니다.`);
    }

    const onProtect = (protectReq: IProtectSToC): void => {
        console.log("socket on protect");
        console.log(protectReq);

        setChannelState(protectReq.roomID, true);
        addChatSystemMessage(protectReq.roomID, `채널이 protect 으로 변경되었습니다.`);
    }

    const onMsg = (msgReq: IMsgSToC, myNickName: string): void => {
        console.log("socket on msg");
        console.log(msgReq);

        if (isBlocked(msgReq.nick)) {
            return;
        }

        addUserMessageInAccessChannel(msgReq, myNickName);
    }

    const onDM = (DMReq: IDMSToC, myNickName: string): void => {
        console.log(`socket on dm`);
        console.log(DMReq);

        if (isBlocked(DMReq.from)) {
            return;
        }

        const DMMessage: IDMInfo = {
            id: Date.now(),
            isUser: myNickName === DMReq.from,
            isSystem: false,
            message: DMReq.message,
            from: DMReq.from,
            to: DMReq.to,
        }

        setDMessages((prevDMSocketMessage) => [...prevDMSocketMessage, DMMessage]);


        let selectNum = "";
        setContentSelectNum(prev => {
            selectNum = prev;
            return prev;
        })

        if (selectNum !== "4") {
            setDMNotiData(DMReq);
        }
    }

    const onBlock = (blockReq: IBlockSToC): void => {
        console.log("socket on block");
        console.log(blockReq);

        addBlockUser(blockReq.nick);
    }

    const onUnBlock = (unBlockReq: IUnBlockSToC): void => {
        console.log("socket on unblock");
        console.log(unBlockReq);

        removeBlockedUser(unBlockReq.nick);
    }

    const onFriend = (friendReq: IFriendSToC): void => {
        console.log("socket on friend");
        console.log(friendReq);

        const friendInfo: IFriendInfo = {
            nick: friendReq.nick,
            status: friendReq.status
        }

        setFriends((prevFriendInfos: IFriendInfo[]) => {
            return [...prevFriendInfos, friendInfo]
        })
    }

    const onUnFriend = (unFriendReq: IUnFriendSToC): void => {
        console.log("socket on unfriend");
        console.log(unFriendReq);

        setFriends((prevFriendInfos: IFriendInfo[]) => {
            const newFriendInfos: IFriendInfo[] = prevFriendInfos.filter((friendInfo: IFriendInfo) => friendInfo.nick !== unFriendReq.nick);
            return [...newFriendInfos];
        })
    }

    const onReject = (reject: IRejectSToC): void => {
        console.log("socket on reject");
        console.log(reject);
        
        alert(reject.message);
    }

    //Chatting
    //=========================================================================================================================================================
    const [p1Score, setP1Score] = useState<number>(0);
    const [p2Score, setP2Score] = useState<number>(0);
    //=========================================================================================================================================================
    //Game

    const [bMatched, setMatched] = useState<boolean>(false);
    const [matchedNames, setMatchedNames] = useState<IMatchedSToC>(null);

    //Match
    const [bWait, setWaiting] = useState<boolean>(false);

    const onChallenge = (challengeReq: IChallengeStoC): void => {
        console.log("socket on challenge");
        console.log(challengeReq);

        //openNotification(challengeReq);        
    }

    const onUnMatched = (): void => {
        console.log("socket on unmatched");
        console.log("empty");

        alert("Game UnMatched");
        setWaiting(false);
        setMatched(false);
    }

    const onMatched = (matchedReq: IMatchedSToC): void => {
        console.log("socket on matched")
        console.log(matchedReq)

        setP1Score(0);
        setP2Score(0);
        setMatchedNames(matchedReq);
        setContentSelectNum("2");
        setMatched(true);
        setWaiting(false);
    }

    const onScore = (scoreReq: IScoreSToC): void => {
        console.log("socket on score")
        console.log(scoreReq)

        setP1Score((prev) => {
            if (scoreReq.scorer === "p1") {
                console.log("win p1");
                return prev + 1
            }
            return prev;
        })

        setP2Score((prev) => {
            if (scoreReq.scorer === "p2") {
                console.log("win p2");
                return prev + 1
            }
            return prev;
        })
    }

    const onFin = (emptyReq): void => {
        console.log("socket on fin")
        console.log("empty")

        const newFin: IFinNoti = {
            message: emptyReq.message
        }

        SetGameMessage(newFin);
        setMatched(false);
    }

    const onNotGaming = (): void => {
        console.log("socket on notgaming")
        console.log("empty")
    }
    //Game
    //=========================================================================================================================================================

    //Socket On
    //=========================================================================================================================================================

    const [challengeNotiData, setChallengeNotiData] = useState<IChallengeStoC>(null);

    useEffect(() => {
        if (challengeNotiData) {
            const key = Date.now();
            notification.open({
                message: `Game Requested ${challengeNotiData.mode}`,
                description: `A game has been requested by ${challengeNotiData.nick}.`,
                btn: [
                    <Button key="confirm" type="primary" size="small" onClick={() => {
                        const takeCToS: ITakeCToS = {
                            ftLogin: challengeNotiData.ftLogin
                        }
                        socket?.emit("take", takeCToS);
                        console.log("socket emit take");
                        console.log(takeCToS)
                        notification.destroy();
                    }}>
                        Yes
                    </Button>,
                ],
                key: key,
                duration: 30,
                onClose: () => {
                    const refuseCToS: IRefuseCToS = {
                        ftLogin: challengeNotiData.ftLogin
                    }
                    socket?.emit("refuse", refuseCToS);
                    console.log("socket emit refuse");
                    console.log(refuseCToS);
                }
            });
        }
        return () => {
        };
    }, [challengeNotiData]);

    const [DMNotiData, setDMNotiData] = useState<IDMSToC>(null);
    useEffect(() => {

        if (DMNotiData) {
            const key = Date.now();
            notification.open({
                message: `From ${DMNotiData.from}`,
                description: `${DMNotiData.message}`,
                key: key,
                duration: 4,
            });
        }
        return () => {
            //notification.destroy();
        };

    }, [DMNotiData]);

    const [GameMessage, SetGameMessage] = useState<IFinNoti>();
    useEffect(() => {
        if (GameMessage) {
            const key = Date.now();
            notification.open({
                message: `Game`,
                description: `${GameMessage.message}`,
                key: key,
                duration: 4,
            });
        }
        return () => {
        };
    }, [GameMessage]);




    //effect
    useEffect(() => {

        //let myNickName: string = "NONE";

        axios.get(`${server_uri}/users/mynick`).then(response => {
            setNickName(response.data);
            setMenuMount(true);
            console.log(`nick data ${response.data}`);            
        }).catch(err => { setMenuMount(false);  router.push("/login")} );        

        const socket = io(`${server_uri}`, { transports: ['websocket'] });

        //=========================================================================================================================================================
        //Chatting
        socket?.on(`chans`, (chansReq: IChansSToC) => {
            onChans(chansReq);
        });

        socket?.on("blocks", (blocksReq: IBlocksSToC) => {
            onBlocks(blocksReq);
        })

        socket?.on("friends", (friendsReq: IFriendsSToC) => {
            onFriends(friendsReq);
        })

        socket?.on("state", (stareReq: IStateSToC) => {
            onState(stareReq);
        })

        socket?.on("nick", (nickReq: INickSToC) => {

            let myNickName: string = "NONE";
            setNickName(prev => {
                myNickName = prev;
                return prev;
            });

            onNick(nickReq, myNickName);
        })

        socket?.on(`open`, (openChannel: IOpenSToC) => {
            onOpen(openChannel);
        });

        socket?.on("close", (closeReq: ICloseSToC) => {
            onClose(closeReq);
        })

        socket?.on(`join`, (joinReq: IJoinSToC) => {

            let myNickName: string = "NONE";
            setNickName(prev => {
                myNickName = prev;
                return prev;
            });

            onJoin(joinReq, myNickName);
        });

        socket?.on("users", (usersReq: IUsersSToC) => {
            onUsers(usersReq)
        });

        socket?.on("leave", (leaveReq: ILeaveSToC) => {

            let myNickName: string = "NONE";
            setNickName(prev => {
                myNickName = prev;
                return prev;
            });

            onLeave(leaveReq, myNickName);
        })

        socket?.on("admin", (adminReq: IAdminSToC) => {
            onAdmin(adminReq);
        })

        socket?.on("kick", (kickReq: IKickSToC) => {

            let myNickName: string = "NONE";
            setNickName(prev => {
                myNickName = prev;
                return prev;
            });

            onKick(kickReq, myNickName);
        })

        socket?.on("ban", (banReq: IBanSToC) => {

            let myNickName: string = "NONE";
            setNickName(prev => {
                myNickName = prev;
                return prev;
            });

            onBan(banReq, myNickName);
        })

        socket?.on("mute", (muteReq: IMuteSToC) => {
            onMute(muteReq);
        })

        socket?.on("unmute", (unMuteReq: IUnMuteSToC) => {
            onUnMute(unMuteReq);
        })

        socket?.on("public", (publicReq: IPublicSToC) => {
            onPublic(publicReq);
        })

        socket?.on("private", (privateReq: IPrivateSToC) => {
            onPrivate(privateReq);
        })

        socket?.on("protect", (protectReq: IProtectSToC) => {
            onProtect(protectReq);
        })

        socket?.on("msg", (msgReq: IMsgSToC) => {

            let myNickName: string = "NONE";
            setNickName(prev => {
                myNickName = prev;
                return prev;
            });

            onMsg(msgReq, myNickName);
        })

        socket?.on("dm", (DMMessageReq: IDMSToC) => {

            let myNickName: string = "NONE";
            setNickName(prev => {
                myNickName = prev;
                return prev;
            });

            onDM(DMMessageReq, myNickName);
        });

        socket?.on("block", (blockReq: IBlockSToC) => {
            onBlock(blockReq);
        })

        socket?.on("unblock", (unBlockReq: IUnBlockSToC) => {
            onUnBlock(unBlockReq);
        })

        socket?.on("friend", (friendReq: IFriendSToC) => {
            onFriend(friendReq);
        })

        socket?.on("unfriend", (unFriendReq: IUnFriendSToC) => {
            onUnFriend(unFriendReq);
        })

        socket?.on("reject", (rejectReq: IRejectSToC) => {

            onReject(rejectReq);
        })
        //Chatting
        //=========================================================================================================================================================



        //=========================================================================================================================================================
        //Game

        // 이 부분에서 notification 사용을 처리

        socket?.on("challenge", (challengeReq: IChallengeStoC) => {
            // 이 부분에서 notification을 보여주기 전에 onChallenge를 호출
            onChallenge(challengeReq);
            setChallengeNotiData(challengeReq);
        });

        socket?.on("unmatched", (emptyReq) => {
            onUnMatched();
        })

        socket?.on("matched", (matchedReq: IMatchedSToC) => {
            onMatched(matchedReq);
        })

        socket?.on("fin", (emptyReq) => {
            onFin(emptyReq);
        })

        socket?.on("notgaming", (emptyReq) => {
            onNotGaming();
        })

        socket?.on("score", (scoreSToC: IScoreSToC) => {
            onScore(scoreSToC)
        })

        socket?.on("waiting", emptyReq => {

            console.log("socket on waiting");
            setWaiting(true);
        })

        socket?.on("reject-game", (response: {message: string} ) => {
            console.log("socket on reject-game");
            alert(response.message);    
        });
        //Game
        //=========================================================================================================================================================

        setSocket(socket);

        return () => {
            socket.disconnect();
        };

    }, []);

    const router = useRouter()

    //logout
    //window.location.href = "/login"
    const onClickLogout = (): void => {
        axios.post(`${server_uri}/auth/logout`).then(response => {
            setMenuMount(false);
            router.push("/login");
        }).catch(err => { });

    }

    return (
        <div>
            <Layout hasSider>
                <Sider
                    style={{
                        overflow: 'auto',
                        height: '100vh',
                        position: 'fixed',
                        left: 0,
                        top: 0,
                        bottom: 0,
                    }}>
                    <div className="demo-logo-vertical" />

                    <Menu theme="dark" mode="inline" defaultSelectedKeys={['1']} items={bMenuMount ? itemses : undefined} onClick={onClickProfile} />

                    {/* 로그아웃 버튼 */}

                    <div style={{ position: 'absolute', bottom: 0, width: '100%', padding: '16px', background: '#001529' }}>
                        <Button type="primary" onClick={onClickLogout}> Logout </Button>
                    </div>


                </Sider>

                <Layout className="site-layout" style={{ marginLeft: 200 }}>

                    {selectContentNum === `1` ? <ProfilePage
                        socket={socket}
                        nickName={nickName}                        
                        setNickName={setNickName}
                    /> : <div></div>}


                    {selectContentNum === `8` ? <UserProfilePag
                        socket={socket}
                        nickName={nickName}

                        friends={friends}
                        blockList={blockList}



                    /> : <div></div>}


                    {selectContentNum === `2` ? <GamePage
                        socket={socket}
                        setMatchedNames={setMatchedNames}
                        setP1Score={setP1Score}
                        setP2Score={setP2Score}
                        bWait={bWait}
                        bMatched={bMatched}
                    /> : <div></div>}

                    {selectContentNum === `3` ? <ChatPage
                        socket={socket}
                        nickName={nickName}
                        accessChannels={accessChannels}
                        selectedChannel={selectedAccessChannel}
                        channelMessages={accessChannelsMessages}
                        usersArray={accessChannelsUsersArray}

                        friends={friends}
                        blockList={blockList}

                        nickName={nickName}


                        AddUserMessage={addUserMessageInAccessChannel}
                        handleChannelSelect={onClickChannel}

                    /> : <div></div>}

                    {selectContentNum === `4` ? <DMPage
                        socket={socket}
                        nickName={nickName}
                        DMessages={DMessages}
                    /> : <div></div>}

                    {selectContentNum === `5` ? <ChannelListPage

                        socket={socket}
                        channels={listUpChannels}
                    /> : <div></div>}

                    {selectContentNum === `6` ? <FriendListPage
                        socket={socket}

                        nickName={nickName}
                        friends={friends}
                        blockList={blockList}

                        addFriend={addFriend}
                        removeFriend={removeFriend}
                    /> : <div></div>}


                    {selectContentNum === `7` ? <BlockListPage
                        socket={socket}
                        blockedUsers={blockList}
                    /> : <div></div>}

                </Layout>


                {/*Reject 모달*/}


            </Layout>
        </div>
    )
}
