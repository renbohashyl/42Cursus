import React, { useState } from "react";
import { Modal, Button, Input, List, Typography, Form } from "antd";
import { socket } from "../../../../pages/socket";

interface IBlockCToS {
    nick: string
}

interface IUnBlockCToS {
    nick: string
}

const BlockPage: React.FC = (props) => {


    const [blockUserModalVisible, setBlockUserModalVisible] = useState<boolean>(false);
    const [unblockUserModalVisible, setUnblockUserModalVisible] = useState<boolean>(false);
    const [blockedUserName, setBlockedUserName] = useState<string>("");
    const [blockedUserReason, setBlockedUserReason] = useState<string>("");
    const [userToUnblock, setUserToUnblock] = useState<string>("");

    const socket = props.socket;
    const blockedUsers : string[] = props.blockedUsers;    

    const onClickShowBlockModal = () => {
        setBlockUserModalVisible(true);
    };

    const onClickShowUnBlockModal = () => {
        setUnblockUserModalVisible(true);
    };

    const onClickBlockModalNo = () => {
        setBlockUserModalVisible(false);
        setBlockedUserName("");
        setBlockedUserReason("");
    };

    const onClickBlockUserModalOK = () => {
        //props.addBlockUser(blockedUserName);

        const blockUser : IBlockCToS = {                        
            nick: blockedUserName
        }

        socket.emit("block", blockUser);
        console.log("socket emit block");
        console.log(blockUser);        

        setBlockUserModalVisible(false);
        setBlockedUserName("");
        setBlockedUserReason("");
    };
    
    const onUnblockUserCancel = () => {
        setUnblockUserModalVisible(false);
        setUserToUnblock("");
    };

    const onUnblockUserConfirm = () => {
        //props.removeBlockedUser(userToUnblock);

        const unBlockUser : IUnBlockCToS = {                        
            nick: userToUnblock
        }

        socket.emit("unblock", unBlockUser);
        console.log("socket emit unblock");
        console.log(unBlockUser);

        setUnblockUserModalVisible(false);
        setUserToUnblock("");
    };


        

    return (
        <div style={{ padding: "20px" }}>
            
            {/* 차단된 사용자 목록 */}
            <List
                itemLayout="horizontal"
                dataSource={blockedUsers}
                renderItem={(user) => (
                    <List.Item
                        style={{
                            border: "1px solid #ccc",
                            marginBottom: "10px",
                            padding: "10px",
                            display: "flex",
                            justifyContent: "space-between",
                            alignItems: "center",
                        }}
                    >
                        <div>
                            <Typography.Text>{user}</Typography.Text>
                        </div>                        
                    </List.Item>
                )}
            />

            {/* 사용자 차단 버튼 */}
            <Button
                type="primary"
                style={{ marginTop: "10px" }}
                onClick={onClickShowBlockModal}
            >
                사용자 차단
            </Button>

            {/* 사용자 차단 해제 버튼 */}
            <Button
                type="danger"
                style={{ marginTop: "10px", marginLeft: "10px" }}
                onClick={onClickShowUnBlockModal}
            >
                사용자 차단 해제
            </Button>

            {/* 사용자 차단 모달 */}
            <Modal
                title="사용자 차단"
                open={blockUserModalVisible}
                onCancel={onClickBlockModalNo}
                onOk={onClickBlockUserModalOK}
            >
                <Form>
                    <Form.Item label="사용자 이름">
                        <Input
                            value={blockedUserName}
                            onChange={(e) => setBlockedUserName(e.target.value)}
                        />
                    </Form.Item>                  
                </Form>
            </Modal>

            {/* 사용자 차단 해제 모달 */}
            <Modal
                title="사용자 차단 해제"
                open={unblockUserModalVisible}
                onCancel={onUnblockUserCancel}
                onOk={onUnblockUserConfirm}
            >
                <Form>
                    <Form.Item label="차단 해제할 사용자 이름">
                        <Input
                            value={userToUnblock}
                            onChange={(e) => setUserToUnblock(e.target.value)}
                        />
                    </Form.Item>
                </Form>
            </Modal>
        </div>
    );
};

export default BlockPage;
