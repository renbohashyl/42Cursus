import React, { useState, useRef, useEffect } from "react";
import { Button, Modal, Input, Select, Radio } from "antd";
import { ILeaveCToS } from "../Interface";
import ShowUserProfilePage from "../../../Profile/OtherProfile";

interface IMessage {
    id: number;
    text: string;
    isUser: boolean;
    isSystem: boolean,
    from: string;
}

interface IPublicCToS {
    roomID: number
}

interface IPrivateCToS {
    roomID: number
}

interface IProtectCToS {
    roomID: number,
    password: string
}

interface IAdminCToS {
    roomID: number,
    nick: string
}

interface IKickCToS {
    roomID: number,
    nick: string
}

interface IBanCToS {
    roomID: number,
    nick: string
}

interface IChallengeCToS {
    nick: string,
    mode: string
}

import {
    IChatMessageCtoS,
    IUsersSToC,
    IChannelInfo,
} from "../Interface"
import Password from "antd/es/input/Password";


interface IMuteCToS {
    roomID: number,
    nick: string,
    timeInSec: number
}

const ChatPage: React.FC = (props) => {

    const socket = props.socket;
    const channelMessages = props.channelMessages
    const accessChannels: IChannelInfo[] = props.accessChannels
    const selectedChannel: IChannelInfo = props.selectedChannel
    const handleChannelSelect = props.handleChannelSelect
    const AddUserMessage = props.AddUserMessage
    const usersArray: IUsersSToC[] = props.usersArray

    const [inputText, setInputText] = useState<string>("");

    const [isInviteModalVisible, setIsInviteModalVisible] = useState<boolean>(false);
    const [isAdminModalVisible, setIsAdminModalVisible] = useState<boolean>(false);
    const [isMuteModalVisible, setIsMuteModalVisible] = useState<boolean>(false); // Mute Modal 추가
    const [isGameModalVisible, setIsGameModalVisible] = useState<boolean>(false); // Mute Modal 추가
    const [isUserInfoVisible, setIsUserInfoVisible] = useState<boolean>(false);

    const [muteUser, setMuteUser] = useState<string>(""); // Mute할 유저의 이름
    const [muteDuration, setMuteDuration] = useState<number>(0); // Mute 지속 시간 (초)
    const [selectedMode, setSelectedMode] = useState('standard');

    const [inviteInput, setInviteInput] = useState<string>("");
    const [adminInput, setAdminInput] = useState<string>("");
    const [gameInput, setGameInput] = useState<string>("");

    const textareaRef = useRef<HTMLTextAreaElement | null>(null);
    const messageContainerRef = useRef<HTMLDivElement | null>(null);


    // New state variables for room settings
    const [isRoomSettingsModalVisible, setIsRoomSettingsModalVisible] = useState<boolean>(false);
    const [roomType, setRoomType] = useState<"public" | "private" | "protected">("public");
    const [password, setPassword] = useState<string>("");




    //=============================================================================
    //Kick ban    
    const [isKickModalVisible, setIsKickModalVisible] = useState<boolean>(false);
    const [isBanModalVisible, setIsBanModalVisible] = useState<boolean>(false);
    const [kickUser, setKickUser] = useState<string>("");
    const [banUser, setBanUser] = useState<string>("");

    const [clickUserName, setClickUserName] = useState("");

    const onClickShowKickModal = () => {
        setIsKickModalVisible(true);
    };

    const onClickShowBanModal = () => {
        setIsBanModalVisible(true);
    };

    const handleKickModalOk = () => {
        // Implement the logic to kick the user using the socket
        // Emit an event to the server to perform the kick action

        // Example code (replace with actual socket.emit code):
        const kickUserAction: IKickCToS = {
            roomID: selectedChannel.roomID,
            nick: kickUser,
        };

        socket?.emit("kick", kickUserAction);
        console.log("socket emit kick");
        console.log(kickUserAction);

        setIsKickModalVisible(false);
        setKickUser("");
    };

    const handleBanModalOk = () => {
        // Implement the logic to ban the user using the socket
        // Emit an event to the server to perform the ban action

        // Example code (replace with actual socket.emit code):
        const banUserAction: IBanCToS = {
            roomID: selectedChannel.roomID,
            nick: banUser,
        };

        socket?.emit("ban", banUserAction);
        console.log("socket emit ban");
        console.log(banUserAction);

        setIsBanModalVisible(false);
        setBanUser("");
    };
    //Kick ban
    //=============================================================================


    // Function to handle opening the Room Settings modal
    const handleRoomSettingsClick = () => {
        setIsRoomSettingsModalVisible(true);
    };

    // Function to handle OK button in Room Settings modal
    const handleRoomSettingsModalOk = () => {
        // Handle the room settings here, e.g., emit to server or update state
        console.log(roomType);
        console.log(password);

        if (roomType === "public") {

            const publicCToS: IPublicCToS = {
                roomID: selectedChannel.roomID
            }

            socket?.emit("public", publicCToS)
            console.log("socket emit public");
            console.log(publicCToS);
        }
        else if (roomType === "private") {

            const privateCToS: IPrivateCToS = {
                roomID: selectedChannel.roomID
            }

            socket?.emit("private", privateCToS)
            console.log("socket emit private");
            console.log(privateCToS);
        }
        else if (roomType === "protected") {

            const protectCToS: IProtectCToS = {
                roomID: selectedChannel.roomID,
                password: password
            }

            socket.emit("protect", protectCToS)
            console.log("socket emit protect");
            console.log(protectCToS);
        }

        setIsRoomSettingsModalVisible(false);
        setPassword("");        
    };




    useEffect(() => {
        if (messageContainerRef.current) {
            messageContainerRef.current.scrollTop = messageContainerRef.current.scrollHeight;
        }
    }, [channelMessages]);

    const onClickLeaveButton = (channel: IChannelInfo) => {

        const leaveCToS: ILeaveCToS = {
            roomID: channel.roomID
        }

        socket?.emit("leave", leaveCToS);
        console.log("socket emit leave");
        console.log(leaveCToS);

    };

    const onClickAllRemoveButton = () => {
        console.log("제거");
        accessChannels.map(channel => onClickLeaveButton(channel));
    }

    const handleKickUser = (channel: IChannelInfo, user: string) => {
        console.log(`Kicking user: ${user} from channel: ${channel.name}`);
    };

    const handleInviteUser = () => {
        setIsInviteModalVisible(true);
    };

    const onClickAdminButton = () => {
        setIsAdminModalVisible(true);
    };

    const handleMuteUserClick = () => {
        setIsMuteModalVisible(true); // Mute Modal 열기
    };

    const onClickShowGameModal = () => {
        setIsGameModalVisible(true);
    }

    const handleInviteModalOk = () => {
    };

    const onClickGameModalOk = () => {

        const challengeCToS: IChallengeCToS = {
            nick: gameInput,
            mode: selectedMode
        }

        socket?.emit("challenge", challengeCToS);
        console.log("socket emit challenge");
        console.log(challengeCToS);

        setGameInput("");
        setIsGameModalVisible(false);
    }

    const onClickAdminModalOK = () => {

        const adminCToS: IAdminCToS = {
            roomID: selectedChannel.roomID,
            nick: adminInput
        }

        socket?.emit("admin", adminCToS);
        console.log("socket emit admin");
        console.log(adminCToS);

        setIsAdminModalVisible(false); // Mute Modal 닫기
    };



    const onClickMuteModalOkButton = () => {
        if (muteUser && muteDuration > 0) {

            const muteCToS: IMuteCToS = {
                roomID: selectedChannel.roomID,
                nick: muteUser,
                timeInSec: muteDuration
            }

            socket?.emit("mute", muteCToS);
            console.log("socket emit mute");
            console.log(muteCToS);

            setMuteUser("");
            setMuteDuration(0);
            setIsMuteModalVisible(false); // Mute Modal 닫기            
        }
    };



    const enterKeyPress = (e: React.KeyboardEvent<HTMLTextAreaElement>) => {
        if (e.key === "Enter" && !e.shiftKey) {

            e.preventDefault();
            if (selectedChannel && inputText.trim() !== "") {

                const chatMessageCtoS: IChatMessageCtoS = {
                    roomID: selectedChannel.roomID,
                    message: inputText,
                };

                socket?.emit("msg", chatMessageCtoS);
                console.log("socket emit msg");
                console.log(chatMessageCtoS);

                setInputText("");
            }
        }
    };


    const handleModalCancel = () => {
        setIsInviteModalVisible(false);
        setInviteInput("");

        setIsAdminModalVisible(false);
        setAdminInput("");

        setIsMuteModalVisible(false);
        setMuteUser("");

        setIsRoomSettingsModalVisible(false);
        setPassword("");

        setIsKickModalVisible(false);
        setKickUser("");

        setIsBanModalVisible(false);
        setBanUser("");

        setIsGameModalVisible(false);
        setGameInput("");

        setIsUserInfoVisible(false);

        setMuteDuration(0);
    };

    const onClickShowUserProfileModal = (userName): void => {
        console.log(userName);
    }

    const onClickUser = (userName): void => {

        console.log(userName);
        if (userName == "" || userName === null) {
            return;
        }

        setClickUserName(userName);
        setIsUserInfoVisible(true);

    }

    return (
        <div style={{ display: "flex", flexDirection: "row", height: "100vh", background: "#f4f4f4", overflow: "hidden" }}>
            <div style={{ width: "20%", background: "#f0f0f0", padding: "10px", boxShadow: "0px 0px 10px rgba(0, 0, 0, 0.2)", overflowY: "auto" }}>

                {selectedChannel && (<Button type="primary" size="small" onClick={onClickShowGameModal} style={{ marginLeft: "5px" }}>
                    Game
                </Button>)}

                {selectedChannel && (<Button type="primary" size="small" onClick={handleMuteUserClick} style={{ marginLeft: "5px" }}>
                    Mute
                </Button>)}

                {selectedChannel && (<Button type="primary" size="small" onClick={onClickAdminButton} style={{ marginLeft: "5px" }}>
                    Admin
                </Button>)}

                {selectedChannel && (<Button type="primary" size="small" onClick={handleRoomSettingsClick} style={{ marginLeft: "5px" }}>
                    Room Settings
                </Button>)}

                {selectedChannel && (
                    <Button type="primary" size="small" onClick={onClickShowKickModal} style={{ marginLeft: "5px" }}>
                        Kick
                    </Button>
                )}

                {selectedChannel && (
                    <Button type="primary" size="small" onClick={onClickShowBanModal} style={{ marginLeft: "5px" }}>
                        Ban
                    </Button>
                )}



                {accessChannels.map((channel: IChannelInfo) => (
                    <div
                        key={channel?.roomID}
                        style={{
                            marginBottom: "10px",
                            padding: "5px",
                            borderRadius: "5px",
                            display: "flex",
                            justifyContent: "space-between",
                            alignItems: "center",
                            cursor: "pointer",
                            background: selectedChannel === channel ? "#0d6efd" : "#fff",
                            border: selectedChannel === channel ? "1px solid #0d6efd" : "1px solid #ccc",
                        }}
                        onClick={() => handleChannelSelect(channel)}
                    >
                        {channel?.name}
                    </div>
                ))}


                {selectedChannel && (
                    <div style={{ paddingTop: "10px" }}>
                        Users in {" "} {selectedChannel.name}:
                        {
                            // owner
                            usersArray.map(usersSToC => {
                                if (usersSToC?.roomID == selectedChannel?.roomID) {
                                    return (
                                        <div key={selectedChannel?.roomID}>
                                            {
                                                <div style={{ display: "flex", justifyContent: "space-between", alignItems: "center", padding: "5px" }} onClick={() => onClickUser(usersSToC.ownerOrNull)}>
                                                    owner {usersSToC.ownerOrNull && usersSToC.ownerOrNull}
                                                </div>
                                            }
                                        </div>
                                    );
                                }
                                return null;
                            })}
                        {
                            //member or admin
                            usersArray.map(usersSToC => {
                                if (usersSToC?.roomID == selectedChannel?.roomID) {
                                    return (
                                        <div key={selectedChannel?.roomID}>
                                            {
                                                [...usersSToC?.users].map((userInfo, index) => {
                                                    return (
                                                        <div key={index} style={{ display: "flex", justifyContent: "space-between", alignItems: "center", padding: "5px" }} onClick={() => onClickUser(userInfo.nick)}>
                                                            {userInfo.isAdmin ? "admin" : "member"} {userInfo.nick}
                                                        </div>
                                                    );

                                                })
                                            }
                                        </div>
                                    );
                                }
                                return null;
                            })}
                    </div>
                )}



            </div>
            <div style={{ width: "80%", display: "flex", flexDirection: "column", justifyContent: "space-between", overflow: "hidden" }}>

                <div
                    ref={messageContainerRef}
                    style={{
                        flex: "1",
                        maxHeight: "80vh",
                        overflowY: "auto",
                        border: "1px solid #ccc",
                        borderRadius: "5px",
                        padding: "10px",
                        background: "#fff",
                        boxShadow: "0px 0px 10px rgba(0, 0, 0, 0.2)",
                        margin: "20px",
                    }}
                >
                    {channelMessages[selectedChannel?.roomID || 0]?.map((message) => (
                        <div
                            key={message.id}
                            style={{
                                marginBottom: "10px",
                                padding: "5px 10px",
                                borderRadius: "5px",
                                background: message.isSystem ? "##f0f0f0" : (message.isUser ? "#0d6efd" : "#f0f0f0"),
                                color: message.isSystem ? "#FFA000" : (message.isUser ? "#fff" : "#333"),
                                alignSelf: message.isUser ? "flex-end" : "flex-start",
                                textAlign: message.isSystem ? "center" : (message.isUser ? "right" : "left"),
                            }}
                        >
                            <div style={{
                                fontSize: "12px", color: "#888", marginBottom: "4px",
                                textAlign: message.isSystem ? "center" : (message.isUser ? "right" : "left")
                            }}>
                                {message.isSystem ? "System" : (message.isUser ? `To ${message.from}` : `From ${message.from}`)}
                            </div>
                            {message.text}
                        </div>
                    ))}
                </div>

                <div style={{ padding: "10px", overflow: "hidden" }}>
                    <textarea
                        ref={textareaRef}
                        value={inputText}
                        onChange={(e) => setInputText(e.target.value)}
                        onKeyPress={enterKeyPress}
                        placeholder={selectedChannel ? "Type your message..." : "Select a channel to start chatting."}
                        rows={4}
                        style={{ padding: "10px", borderRadius: "5px", border: "1px solid #ccc", resize: "none", width: "100%" }}
                        disabled={!selectedChannel}
                    />

                    <div style={{ display: "flex", justifyContent: "flex-end", paddingTop: "10px" }}>
                        {selectedChannel && (
                            <Button type="danger" size="small" onClick={() => onClickLeaveButton(selectedChannel)}>
                                Leave
                            </Button>
                        )}

                        {/* <Button type="danger" size="small" onClick={onClickAllRemoveButton}>
                                All Leave
                            </Button> */}



                    </div>


                </div>
            </div>

            {/* 게임요청 */}
            <Modal title="Game" open={isGameModalVisible} onOk={onClickGameModalOk} onCancel={handleModalCancel}>
                <Input value={gameInput} onChange={(e) => setGameInput(e.target.value)} placeholder="Enter user name" />

                <Select
                    value={selectedMode}
                    onChange={(value) => setSelectedMode(value)}
                    placeholder="Select Game Mode"
                    style={{ marginTop: "10px" }}
                >
                    <Select.Option value="standard"> standard  </Select.Option>
                    <Select.Option value="deathmatch">  deathmatch </Select.Option>
                </Select>

            </Modal>

            <Modal title="Invite User" open={isInviteModalVisible} onOk={handleInviteModalOk} onCancel={handleModalCancel}>
                <Input value={inviteInput} onChange={(e) => setInviteInput(e.target.value)} placeholder="Enter user name" />
            </Modal>

            <Modal title="Add Admin" open={isAdminModalVisible} onOk={onClickAdminModalOK} onCancel={handleModalCancel}>
                <Input value={adminInput} onChange={(e) => setAdminInput(e.target.value)} placeholder="Enter user name" />
            </Modal>


            {/* Mute Modal */}
            <Modal title="Mute User" open={isMuteModalVisible} onOk={onClickMuteModalOkButton} onCancel={handleModalCancel}>
                <Input value={muteUser} onChange={(e) => setMuteUser(e.target.value)} placeholder="Enter user name" />


                <Select
                    value={muteDuration}
                    onChange={(value) => setMuteDuration(value)}
                    placeholder="Select mute duration"
                    style={{ marginTop: "10px" }}
                >
                    <Select.Option value={10}>  10 seconds</Select.Option>
                    <Select.Option value={30}>  30 seconds</Select.Option>
                    <Select.Option value={60}>  1  minute</Select.Option>
                    <Select.Option value={180}> 3  minute</Select.Option>
                    <Select.Option value={300}> 5  minutes</Select.Option>                    
                </Select>
            </Modal>


            {/* Kick Modal */}
            <Modal title="Kick User" open={isKickModalVisible} onOk={handleKickModalOk} onCancel={handleModalCancel}>
                <Input value={kickUser} onChange={(e) => setKickUser(e.target.value)} placeholder="Enter user name" />
            </Modal>

            {/* Ban Modal */}
            <Modal title="Ban User" open={isBanModalVisible} onOk={handleBanModalOk} onCancel={handleModalCancel}>
                <Input value={banUser} onChange={(e) => setBanUser(e.target.value)} placeholder="Enter user name" />
            </Modal>



            {/* Room Settings Modal */}
            <Modal
                title="Room Settings"
                open={isRoomSettingsModalVisible}
                onOk={handleRoomSettingsModalOk}
                onCancel={handleModalCancel}
            >
                <Radio.Group onChange={(e) => setRoomType(e.target.value)} value={roomType}>
                    <Radio value="public">Public</Radio>
                    <Radio value="private">Private</Radio>
                    <Radio value="protected">Protected</Radio>
                </Radio.Group>
                {roomType === "protected" && (
                    <Input
                        value={password}
                        onChange={(e) => setPassword(e.target.value)}
                        placeholder="Enter room password"
                        style={{ marginTop: "10px" }}
                    />
                )}
            </Modal>


            {/*User Info*/}
            <Modal
                title="User Info"
                open={isUserInfoVisible}
                onCancel={handleModalCancel}
                footer={null} // 버튼을 숨김
            >
                <ShowUserProfilePage socket={props?.socket} userName={clickUserName} friends={props?.friends} blockList={props?.blockList} nickName={props?.nickName} />
            </Modal>

        </div>
    );
};

export default ChatPage;
