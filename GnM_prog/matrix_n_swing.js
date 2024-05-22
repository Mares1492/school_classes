
const TANK_STATES = ["isWaitingForAmmo","isPreparingForFire","isFiring","IsAftershot"]
const BALL_STATES = ["isMoving","isMovingNearCannon","isInsideOfTank","isFlying","isHidden"]
let canvas;
let ctx;
let title;
let ballX = 0;
let ballY;
let cannonX;
let cannonY;
let cannonHeight = 100;
let cannonLength = 500;
let angle = 0;
let smokeSpreadMod = 1;
let tankState = TANK_STATES[0];
let ballState = BALL_STATES[0];

const getRandomInt = (min,max) => Math.floor(Math.random()*(max-min+1))+min;

window.onload = () =>{
    canvas = document.getElementById("canvas");
    ctx = canvas.getContext("2d");
    title = document.getElementById("title");
    title.textContent = "The process is infinite"
    cannonY = canvas.height-200;
    cannonX = canvas.width*0.5;
    ballY = canvas.height-50;
    animate();
};

function drowBase() {
    ctx.fillStyle = 'white';
    ctx.strokeStyle = "red";
    ctx.lineWidth =17;
    ctx.beginPath();
    ctx.roundRect(cannonX+(cannonLength*0.5),canvas.height, -cannonLength , -cannonHeight*2,25);
    ctx.roundRect(cannonX+(cannonLength*0.25),cannonY, -cannonLength*0.5 , -cannonHeight,5);
    ctx.stroke();
    ctx.fill();
    ctx.closePath();
}

function handleCannonMovement() {
    if (tankState===TANK_STATES[1]) {
        angle++;
        if(angle>150) {
            tankState = TANK_STATES[2];
            ballState = BALL_STATES[3];
        }
        return;
    }
    if (tankState===TANK_STATES[2]) {
        if(angle>100) {
            angle-=4;
            return;
        }
    }
    if (tankState===TANK_STATES[3]) {
        if(angle>0) {
            angle-=0.5;
            return;
        }
        angle = 0;
        tankState = TANK_STATES[0];
    }
}

function drawCannon() {
    let x = -cannonLength*0.2;    
    let y = cannonHeight*0.8;
    ctx.save();
    ctx.translate(cannonX,cannonY,canvas.height-105)
    ctx.rotate(angle * (Math.PI / 180));

    handleCannonMovement();
 
    ctx.beginPath();
    ctx.strokeStyle = 'white';
    ctx.fillStyle = 'brown';
    ctx.lineWidth = 10;
    ctx.roundRect(x,y-30, -cannonLength ,-cannonHeight,20);
    ctx.stroke();
    ctx.fill();   
    ctx.translate(-cannonX,-cannonY)
    ctx.restore();
    ctx.closePath();

}

function drawBridge() {
    let y = canvas.height-200;
    let x = canvas.width*0.5;
    ctx.beginPath();
    ctx.strokeStyle = "#6082B6"
    ctx.fillStyle = "#B2BEB5"
    ctx.moveTo(x-(cannonLength*3),canvas.width);
    ctx.lineTo(x-(cannonLength*1.3),y+(cannonHeight*0.5));
    ctx.lineTo(x-(cannonLength),y+(cannonHeight*0.5));
    ctx.lineTo(x-(cannonLength),canvas.width);
    ctx.lineWidth = 20;
    ctx.fill()
    ctx.stroke();
    ctx.closePath();

}
  
function drawBall() {
    ctx.beginPath();
    ctx.arc(ballX, ballY, 45, 0, 2 * Math.PI); 
    if (ballState===BALL_STATES[3]) {
        ctx.fillStyle = 'orange';
        ctx.strokeStyle = 'red';
        ctx.lineWidth = 7;
        ctx.stroke();
    }
    else{
        ctx.fillStyle = 'gray';
    }
    ctx.fill();
    ctx.closePath()
}
  
function drawSmoke(x, y, size, opacity) {
    ctx.fillStyle = size<11?`rgba(225,42,4,${opacity})`:`rgba(255, 255, 255, ${opacity})`;
    ctx.fillRect(x, y, size, size);
}

function clearCanvas() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
}

function handleBallMovement() {
    if (ballState === BALL_STATES[0]) {
        ballX += 5; 
        if (ballX >= cannonX-(cannonLength*1.5)) { 
            //near cannon
            ballState = BALL_STATES[1];
        }
    } 
    if(ballState === BALL_STATES[1]){
        if (ballX <= cannonX-(cannonLength*0.8)) {
            ballX += 1.5;
            if (ballY>= cannonY) {
                ballY -= 2;
            }
            return;
        }
        ballX = (canvas.width*0.5) + (cannonLength);
        ballY = canvas.height - cannonLength;
        //inside
        ballState = BALL_STATES[2];
        tankState = TANK_STATES[1];
        smokeSpreadMod = 1;
    }
    if (ballState===BALL_STATES[3]) {
        ballX += 8;
        ballY -= 2;
        if (ballX>=canvas.width) {
            ballState=BALL_STATES[4];
            ballX = -150;
            ballY = canvas.height-50;
        }
    }
}

function handleTankMovement() {
    //firing
    if (tankState === TANK_STATES[2]) {
        cannonX -= 7; 
        if (cannonX <= (canvas.width*0.5)-(canvas.width*0.12)) {
            //aftershot
            tankState = TANK_STATES[3]
        }
    }
    if (tankState === TANK_STATES[3]) {
        if (cannonX <= canvas.width*0.5) {
            cannonX += 2;
        }
        else{
            ballState = BALL_STATES[0]
        }
    }
}

function animate() {
    clearCanvas();
    
    handleBallMovement();
    if (ballState !== BALL_STATES[2]) {
        drawBall();    
    }
    if (tankState===TANK_STATES[2] || tankState === TANK_STATES[3]) {
        let smokeX = (canvas.width*0.5) + (cannonLength);
        let smokeY = canvas.height - cannonLength;
        for (let i = 0; i < 50; i++) {
            drawSmoke(getRandomInt(smokeX-(100*smokeSpreadMod),smokeX+(100*smokeSpreadMod)),getRandomInt(smokeY-(150*smokeSpreadMod),smokeY+(50*smokeSpreadMod)), getRandomInt(1,20)*smokeSpreadMod,Math.random()-(smokeSpreadMod-3));
        }
        smokeSpreadMod+=0.1;
    }
    
    handleTankMovement();
  
    drawCannon();
    drowBase();
    drawBridge();

  
    requestAnimationFrame(animate);
  }
