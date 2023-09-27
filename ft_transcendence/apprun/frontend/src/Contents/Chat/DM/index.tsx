import React, { useState, useRef, useEffect } from "react";
import { IDMCToS, IDMInfo } from "../Interface";

interface IPropsDMPage {
    socket: any,
    DMessages: IDMInfo []
}

const DMPage: React.FC = (props: IPropsDMPage): JSX.Element => {
    const socket = props.socket;
    const DMessages: IDMInfo[] = props.DMessages;    

    const [inputText, setInputText] = useState<string>(""); // 입력된 메시지 텍스트
    const [whisperUser, setWhisperUser] = useState<string>(""); // 귓속말 대상 유저

    const textareaRef = useRef<HTMLTextAreaElement | null>(null);
    const messageContainerRef = useRef<HTMLDivElement | null>(null);

    const changeInputText = (text: string) => {
        setInputText(text);
    };

    const handleKeyPress = (e: React.KeyboardEvent<HTMLTextAreaElement>) => {
        if (e.key === "Enter" && !e.shiftKey) {
            
            e.preventDefault();

            if (inputText.trim() === "" || whisperUser === "") {

                return;
            }
    
            const DMCToS : IDMCToS = {
                nick: whisperUser,
                message: inputText
            }
            
            socket?.emit("dm", DMCToS);        
            console.log("socket emit dm");
            console.log(DMCToS);

            setInputText("");
        }
    };    

    useEffect(() => {
        if (messageContainerRef.current) {
            messageContainerRef.current.scrollTop = messageContainerRef.current.scrollHeight;
        }
    }, [DMessages]);

    return (
        <div style={{ display: "flex", flexDirection: "column", height: "100vh", background: "#f4f4f4" }}>
            <div style={{ width: "100%", display: "flex", flexDirection: "column" }}>
                <div style={{ display: "flex", flexDirection: "row", alignItems: "center", padding: "10px", background: "#fff", boxShadow: "0px 0px 10px rgba(0, 0, 0, 0.2)", margin: "20px", borderRadius: "10px" }}>
                    <div style={{ width: "100%", display: "flex", flexDirection: "column", alignItems: "center", justifyContent: "center" }}>
                        <h2 style={{ fontSize: "24px", fontWeight: "bold", color: "#0d6efd", marginBottom: "20px" }}>Direct Message</h2>
                        <div
                            ref={messageContainerRef}
                            style={{ width: "100%", maxHeight: "90vh", height: "80vh", overflowY: "auto", border: "1px solid #ccc", borderRadius: "5px", padding: "10px", background: "#fff" }}
                        >
                            {DMessages.map((message) => (
                                <div
                                    key={message.id}
                                    style={{
                                        marginBottom: "10px",
                                        padding: "5px 10px",
                                        borderRadius: "5px",
                                        background: message.isSystem ? "##f0f0f0" : (message.isUser ? "#0d6efd" : "#f0f0f0"),                                
                                        color:      message.isSystem ? "#FFA000"  : (message.isUser ? "#fff" : "#333"),
                                        alignSelf:  message.isUser ? "flex-end" : "flex-start",
                                        textAlign:  message.isSystem ? "center"     : (message.isUser ? "right" : "left"),
                                    }}
                                >
                                    <div style={{ fontSize: "12px", color: "#888", marginBottom: "4px", 
                                    textAlign: message.isSystem ? "center" : (message.isUser ? "right" : "left") }}> 
                                              {message.isSystem ? "System" : (message.isUser ? `To ${message.to}` : `From ${message.from}`)}
                                    </div>
                                    {message.message}
                                </div>
                            ))}
                        </div>
                    </div>
                </div>
                <div style={{ display: "flex", justifyContent: "space-between", alignItems: "center", padding: "10px", background: "#fff", boxShadow: "0px 0px 10px rgba(0, 0, 0, 0.2)", margin: "20px", borderRadius: "10px" }}>
                    <div style={{ display: "flex", flexDirection: "column", width: "20%", padding: "10px" }}>
                        <input
                            type="text"
                            placeholder="Whisper to..."
                            value={whisperUser}
                            onChange={(e) => setWhisperUser(e.target.value)}
                            style={{ padding: "5px", borderRadius: "5px", border: "1px solid #ccc", marginBottom: "10px" }}
                        />
                    </div>
                    <textarea
                        ref={textareaRef}
                        value={inputText}
                        onChange={(e) => changeInputText(e.target.value)}
                        onKeyPress={handleKeyPress} // Use onKeyPress instead of onKeyDown
                        placeholder="Type your message..."
                        rows={4}
                        style={{ padding: "10px", borderRadius: "5px", border: "1px solid #ccc", resize: "none", width: "70%" }}
                    />
                </div>
            </div>
        </div>
    );
};

export default DMPage;