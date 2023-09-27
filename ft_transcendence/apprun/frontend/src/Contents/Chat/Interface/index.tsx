// Client to Server

//custom
export interface IDMInfo {
    id: number,
    isUser: boolean,
    isSystem: boolean,
    from: string,
    to: string
    message: string,
}

export interface IChatCreateCToS {
    name: string,
    isProtected: boolean,
    password: string
}

export interface IJoinCToS {
    roomID: number,
    nick: string,
}

export interface IChatLeavCToS {
    roomID: number
}

export interface IChatAdminCToS {
    roomID: number,
    nick: string
}

export interface IChatKickCToS{
    roomID: number, 
    nick: string
}

export interface IChatBanCToS{
    roomID: number,
    nick: string
}

export interface IChatMuteCToS{
    roodID: number,
    nick: string,
    timeInSec: number 
}

export interface IChatPublicCToS {
    roomID: number
}

export interface IChatPrivateCtoS {
    roomID: number
}

export interface IChatProtect {
    roomID: number,
    password: string
}

export interface IChatMessageCtoS {
    roomID: number,
    message: string,
}

export interface IChatJoinCToS {
    roomID: number,
    password: string
}

export interface IChatLeaveCToS {
    roomID: number
}

export interface IDMCToS{
    nick: string, 
    message: string
}
export interface IChatJoinCSToC {
    roomID: number,
    nick: string
}

export interface IBlockedUser {    
    nick: string,
}

export interface IBlockUserSToC {
    nick: string,
}

export interface IBlockUserCToS {
    nick: string,
}

export  interface ILeaveCToS {
    roomID: number,
}








/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Server to Client
export interface IChannelInfo {
    roomID: number,
    isProtected: boolean,    
    name: string,
}

export interface IFriendInfo {
    nick: string,
    status: string    
}

export interface IUserInfo { 
    nick: string,
    isAdmin: boolean,
    isMuted: boolean
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////


export interface IChansSToC {
    chans: IChannelInfo []
}

export interface IBlocksSToC {
    blocks: string []
}

export interface IFriendsSToC {
    friends: IFriendInfo []
}

export interface IStateSToC {
    nick: string, 
    status: string
}

export interface INickSToC {
    oldNick: string,
    newNick: string
}

export interface IOpenSToC {
    roomID: number,
    isProtected: boolean,
    name: string
}

export interface ICloseSToC {
    roomID: number
}

export interface IJoinSToC {
    roomID: number, 
    nick: string, 
    name: string
}

export interface IUsersSToC {
    roomID: number,
    ownerOrNull: string,
    users: IUserInfo []
}

export interface ILeaveSToC {
    roomID: number,
    nick: string,
}

export interface IAdminSToC {
    roomID: number,
    nick: string 
}

export interface IKickSToC {
    roomID: number,
    nick: string
}

export interface IBanSToC {
    roomID: number,
    nick: string
}

export interface IMuteSToC {
    roomID: number,
    nick: string
}

export interface IUnMuteSToC {
    roomID: number,
    nick: string
}

export interface IPublicSToC {
    roomID: number
}

export interface IPrivateSToC {
    roomID: number
}

export interface IProtectSToC {
    roomID: number
}

export interface IMsgSToC {
    roomID: number,
    nick: string,
    message: string
}

export interface IDMSToC {
    from: string,
    to: string,
    message: string
}

export interface IBlockSToC {
    nick: string
}

export interface IUnBlockSToC {
    nick: string
}

export interface IFriendSToC {
    nick: string,
    status: string
}

export interface IUnFriendSToC{
    nick: string
}

export interface IRejectSToC {
    message: string
}
