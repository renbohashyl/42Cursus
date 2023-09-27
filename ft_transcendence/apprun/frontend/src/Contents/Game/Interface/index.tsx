export interface IChallengeStoC {
    nick: string,
    ftLogin: string,
    mode: string
}

export interface IMatchedSToC {
    p1nick: string,
    p2nick: string
}

export interface IVector {
    x: number,
    y: number,
}

export interface IUpdateSToC {
    p1: { pos: IVector, v: IVector },
    p2: { pos: IVector, v: IVector },
    ball: { pos: IVector, v: IVector }
}

export interface IScoreSToC {
    scorer: string    
}


//client to server
export interface IXXXXCToS {
    player: string
}

export interface IChallengeCToS {
    nick: string
}

export interface IControlCToS {
    key: string,
    isPressed: boolean
}
