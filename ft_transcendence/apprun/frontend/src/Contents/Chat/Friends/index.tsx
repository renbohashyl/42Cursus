import React, { useState } from "react";
import { Modal, Button, Input, List, Typography, Form } from "antd";
import ShowUserProfilePage from "../../../Profile/OtherProfile";

interface IFriend {
    id: number;
    name: string;
    status: string;
}

interface IUnfriendCToS {
    nick: string 
}

const FriendListPage: React.FC = (props) => {

    

    const [addFriendModalVisible, setAddFriendModalVisible] = useState<boolean>(false);
    const [deleteFriendModalVisible, setDeleteFriendModalVisible] = useState<boolean>(false);

    const [friendName, setFriendName] = useState<string>("");
    const [friendStatus, setFriendStatus] = useState<string>("");
    const [friendToDelete, setFriendToDelete] = useState<string>("");

    const socket = props.socket;


    const onClickAddFriend = () => {
        setAddFriendModalVisible(true);
    };

    const onClickAddFriendModalYes = () => {
        const newFriend: IFriend = {
            id: Date.now(),
            name: friendName,
            status: friendStatus,
        };

        //props.addFriend(newFriend);

        socket.emit("friend", {nick: friendName});
        console.log("socket emit friend");
        console.log({nick: friendName});

        setAddFriendModalVisible(false);
        setFriendName("");
        setFriendStatus("");
    };


    const onClickAddFriendModalNo = () => {
        setAddFriendModalVisible(false);
        setFriendName("");
        setFriendStatus("");
    };

   

    const onClickRemoveFriendClick = () => {
        setDeleteFriendModalVisible(true);
    };
    const onClickRemoveFriendModalYes = () => {
        //props.removeFriend(friendToDelete);

        const unfriendCToS : IUnfriendCToS = {
            nick: friendToDelete
        }

        socket.emit("unfriend", unfriendCToS);
        console.log("socket emit unfriend");
        console.log(unfriendCToS);

        setDeleteFriendModalVisible(false);
        setFriendToDelete("");
    };
    const onClickRemoveFriendModalNo = () => {
        setDeleteFriendModalVisible(false);
        setFriendToDelete("");
    };    

    const [isUserInfoVisible, setIsUserInfoVisible] = useState<boolean>(false);
    const [clickUserName, setClickUserName] = useState("");


    const onClickUser = (userName : string) : void => {
        setIsUserInfoVisible(true);
        setClickUserName(userName);
    }

    const handleModalCancel = () : void => {
        setIsUserInfoVisible(false);
        setClickUserName("");
    }

    return (
        <div style={{ padding: "20px" }}>
            {/* 친구 목록 */}   
            <List
                itemLayout="horizontal"
                dataSource={props.friends}
                renderItem={(friend) => (
                    <List.Item
                        style={{
                            border: "1px solid #ccc",
                            marginBottom: "10px",
                            padding: "10px",
                            display: "flex",
                            justifyContent: "space-between",
                            alignItems: "center",
                        }}
                        onClick={() => onClickUser(friend?.nick)}                        
                    >
                        <div>
                            <Typography.Text >{friend.nick}</Typography.Text>
                        </div>
                        <Typography.Text type="secondary">{friend.status}</Typography.Text>
                    </List.Item>
                )}
            />

            {/* 친구 추가 버튼 */}
            <Button
                type="primary"
                style={{ marginTop: "10px" }}
                onClick={onClickAddFriend}
            >
                친구 추가
            </Button>

            {/* 친구 삭제 버튼 */}
            <Button
                type="danger"
                style={{ marginTop: "10px", marginLeft: "10px" }}
                onClick={onClickRemoveFriendClick}
            >
                친구 삭제
            </Button>

            {/* 친구 추가 모달 */}
            <Modal
                title="친구 추가"
                open={addFriendModalVisible}
                onOk={onClickAddFriendModalYes}
                onCancel={onClickAddFriendModalNo}
                
            >
                <Form>
                    <Form.Item label="이름">
                        <Input
                            value={friendName}
                            onChange={(e) => setFriendName(e.target.value)}
                        />
                    </Form.Item>                    
                </Form>
            </Modal>

            {/* 친구 삭제 모달 */}
            <Modal
                title="친구 삭제"
                open={deleteFriendModalVisible}
                onOk={onClickRemoveFriendModalYes}
                onCancel={onClickRemoveFriendModalNo}
                
            >
                <Form>
                    <Form.Item label="친구 닉네임">
                        <Input
                            value={friendToDelete}
                            onChange={(e) => setFriendToDelete(e.target.value)}
                        />
                    </Form.Item>
                </Form>
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

export default FriendListPage;
