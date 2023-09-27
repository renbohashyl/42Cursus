import React, { useState, useEffect, useRef } from "react";
import {
  IControlCToS,
  IScoreSToC,
  IUpdateSToC,
  IMatchedSToC,
} from "./Interface";

import { Alert, Space, Spin,notification } from 'antd';
import { Button, Modal, Input, Select, Radio } from "antd";

const paddleWidth = 15;
const paddleHeight = 60;

const screenWidth = 800;
const screenHeight = 450;

const App = (props) => {

  const socket = props.socket;
  const setMatchedNames = props.setMatchedNames;
  const setP1Score = props.setP1Score;
  const setP2Score = props.setP2Score;
  const bWait = props.bWait;
  const bMatched = props.bMatched;

  const canvasRef = useRef(null);
  const ballRef = useRef({
    x: 385,
    y: 225,
    width: paddleWidth,
    height: paddleWidth,
    dx: 5,
    dy: 2,
  });
  const leftPaddleRef = useRef({
    x: 0,
    y: 195,
    width: paddleWidth,
    height: paddleHeight,
    dy: 5,
  });
  const rightPaddleRef = useRef({
    x: 785,
    y: 195,
    width: paddleWidth,
    height: paddleHeight,
    dy: 5,
  });
  const ctxRef = useRef(null);
  const animationFrameIdRef = useRef(null);

  const p12tx = useRef({
    p1Nick: "NONE",
    p2Nick: "NONE",
    p1Score: 0,
    p2Score: 0,
  }
  );

  const update = () => {
  };

  const drawScoresAndNames = () => {
    const ctx = ctxRef.current;
    ctx.fillStyle = 'white';
    ctx.font = '20px Arial';

    const p1tx = `${p12tx.current.p1Nick} ${p12tx.current.p1Score}`
    const p2tx = `${p12tx.current.p2Score} ${p12tx.current.p2Nick}`

    ctx.fillText(p1tx, 10, 30); // Customize the text as needed    
    ctx.fillText(p2tx, screenWidth - 110, 30); // Customize the text as needed
  };

  const drawCenterLine = () => {
    const ctx = ctxRef.current;
    ctx.setLineDash([5, 5]); // Set dash pattern for the line
    ctx.beginPath();
    ctx.moveTo(screenWidth / 2, 0); // Start point of the line (top center)
    ctx.lineTo(screenWidth / 2, screenHeight); // End point of the line (bottom center)
    ctx.strokeStyle = 'white';
    ctx.lineWidth = 2;
    ctx.stroke();
    ctx.setLineDash([]); // Reset dash pattern
  };

  const draw = () => {
    const ctx = ctxRef.current;

    // Clear canvas
    ctx.fillStyle = 'black';
    ctx.fillRect(0, 0, screenWidth, screenHeight);

    // Draw Score
    drawScoresAndNames();

    // Draw paddles
    ctx.fillStyle = 'white';
    ctx.fillRect(leftPaddleRef.current.x, leftPaddleRef.current.y, leftPaddleRef.current.width, leftPaddleRef.current.height);
    ctx.fillRect(rightPaddleRef.current.x, rightPaddleRef.current.y, rightPaddleRef.current.width, rightPaddleRef.current.height);

    // Draw Line
    drawCenterLine();

    // Draw ball
    ctx.fillRect(ballRef.current.x, ballRef.current.y, ballRef.current.width, ballRef.current.height);
  };

  const gameLoop = () => {
    update();
    draw();
    animationFrameIdRef.current = requestAnimationFrame(gameLoop);
  };

  const [bUpKeyPressed, setUpKeyPressed] = useState<boolean>(false);
  const [bDownKeyPressed, setDownKeyPressed] = useState<boolean>(false);

  const keyEventListener = (): void => {
    document.addEventListener('keydown', (event) => {
      if (event.key === "ArrowUp") {
        setUpKeyPressed((prev) => {
          if (prev === false) {

            console.log(event.type);
            const controlCToS: IControlCToS = {
              key: "up",
              isPressed: true
            }
            socket?.emit("control", controlCToS);

            return true;
          }
          return prev;
        });
      }
      if (event.key === "ArrowDown") {
        setDownKeyPressed((prev) => {
          if (prev === false) {
            console.log(event.type);
            const controlCToS: IControlCToS = {
              key: "down",
              isPressed: true
            }
            socket?.emit("control", controlCToS);
            return true;
          }
          return prev;
        });
      }
    });

    document.addEventListener('keyup', (event) => {
      setUpKeyPressed((prev) => {
        if (prev === true) {
          console.log(event.type);
          const controlCToS: IControlCToS = {
            key: "up",
            isPressed: false
          }
          socket?.emit("control", controlCToS);
          return false;
        }
        return prev;
      });

      setDownKeyPressed((prev) => {
        if (prev === true) {
          console.log(event.type);
          const controlCToS: IControlCToS = {
            key: "down",
            isPressed: false
          }
          socket?.emit("control", controlCToS);
          return false;
        }
        return prev;
      });

    });
  }

  const onSocketListener = (): void => {
    socket?.on("update", (updateSToC: IUpdateSToC) => {
      leftPaddleRef.current.x = updateSToC.p1.pos.x;
      leftPaddleRef.current.y = updateSToC.p1.pos.y;

      rightPaddleRef.current.x = updateSToC.p2.pos.x;
      rightPaddleRef.current.y = updateSToC.p2.pos.y;

      ballRef.current.x = updateSToC.ball.pos.x;
      ballRef.current.y = updateSToC.ball.pos.y;

      setMatchedNames((prev: IMatchedSToC) => {
        p12tx.current.p1Nick = prev.p1nick;
        p12tx.current.p2Nick = prev.p2nick;
        return prev;
      })

      setP1Score((prev) => {
        p12tx.current.p1Score = prev;
        return prev;
      })

      setP2Score((prev) => {
        p12tx.current.p2Score = prev;
        return prev;
      })
    })
  }

  const onClickXXXXButton = (): void => {
    console.log("socket emit xxxx");
    socket?.emit("xxxx");
  }

  const onClickTestButton = () => {
    console.log("matchedNames");
  }

  useEffect(() => {
    keyEventListener();
    onSocketListener();

    const canvas = canvasRef.current;
    const ctx = canvas.getContext('2d');
    ctxRef.current = ctx;
    animationFrameIdRef.current = requestAnimationFrame(gameLoop);

    return () => {
      cancelAnimationFrame(animationFrameIdRef.current);
    };
    
  }, []);

  const [isMatching, setIsMatching] = useState(false);

  const onClickLadder = () : void => {
    if (bWait) {      
    } else {
      socket.emit("ladder");
    } 
  }

 


  return (
    <div className="App">
      <canvas ref={canvasRef} width={screenWidth} height={screenHeight}></canvas>

      {/* <div> <button onClick={onClickXXXXButton}> XXXX </button> </div>
      <div> <button onClick={onClickTestButton}> Test </button> </div> */}

    {(!bWait && !bMatched) && (<div> <button onClick={onClickLadder}> {bWait ? "매칭중" : "레더"} </button> </div>) }

    {/* Spin 모달 */}
    {(bWait) && (
        <Spin tip="Loading" size="large">
          <div className="content" />
        </Spin>
    )}
    

    </div>


  );
};

export default App;