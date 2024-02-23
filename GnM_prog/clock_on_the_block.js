let canvas;
let ctx;
const MAX_COUNTER = 360
const SPEED_MOD = 1

window.onload = () =>{
    canvas =document.getElementById("canvas");
    ctx = canvas.getContext("2d")
    ctx.scale(2,-2)
    title = document.getElementById("title")
    const seconds = getCoordinatesBasedOnPoints(60,0.25)
    const minutes = getCoordinatesBasedOnPoints(60,0.20)
    const hours = getCoordinatesBasedOnPoints(12,0.15)
    let secondsIndex = 15;
    let minutesIndex = 15;
    let hoursIndex = 3;
    let secondsCounter = 0;
    let minutesCounter = 0;
    let hoursCounter = 0;
    const initTimer = () => {
        setTimeout(()=>{
            drawArc()
            drawAxis()
            drawIndicator(seconds,secondsIndex,1,"crimson");
            drawIndicator(minutes,minutesIndex,2,"orange");
            drawIndicator(hours,hoursIndex,3,"aqua");
            (secondsIndex-1)<0?secondsIndex=seconds.length-1:--secondsIndex
            secondsCounter++;
            if (((60+1)^secondsCounter)===0) {
                (minutesIndex-1)<0?minutesIndex=minutes.length-1:--minutesIndex
                secondsCounter = 1
                minutesCounter++
            }
            if (((60+1)^minutesCounter)===0) {
                (hoursIndex-1)<0?hoursIndex=hours.length-1:--hoursIndex
                minutesCounter = 1
                hoursCounter++
            }
            title.textContent = (
                (hoursCounter.toString().length===2?hoursCounter:"0"+hoursCounter)
                +":"+
                (minutesCounter.toString().length===2?minutesCounter:"0"+minutesCounter)
                +":"+
                (secondsCounter.toString().length===2?secondsCounter:"0"+secondsCounter)
            )
            
            if (secondsCounter<MAX_COUNTER) {
                return initTimer()
            }
            title.textContent = "This is the end..."
        },1000*SPEED_MOD)
    }
    initTimer()
}

const drawArc = () => {
    ctx.fillStyle = "black"
    ctx.strokeStyle = "white"
    ctx.lineWidth = 1;
    ctx.beginPath()
        ctx.arc(canvas.width*0.25,-canvas.height*0.25,canvas.height*0.24,0, 2 * Math.PI,false)
        ctx.fill()
        ctx.stroke()
    ctx.closePath()
}

const drawIndicator=(seconds,index,size,color)=>{
    ctx.strokeStyle = color
    ctx.lineWidth = size;
    const [x,y]=seconds[index]
    ctx.beginPath()
        ctx.moveTo(canvas.width*0.25,-canvas.height*0.25)
        ctx.lineTo(x,y)
        ctx.stroke()
    ctx.closePath()
}

const drawAxis = () => {
    ctx.strokeStyle = "white"
    ctx.lineWidth = 1;
    ctx.beginPath();
        ctx.moveTo(0,-canvas.height*0.25);
        ctx.lineTo(canvas.width,-canvas.height*0.25);
        ctx.moveTo(canvas.width*0.25,0)
        ctx.lineTo(canvas.width*0.25,-canvas.height*0.50);
        ctx.stroke()
    ctx.closePath();
}

function getCoordinatesBasedOnPoints(numPoints,rMod) {
    const coordinates = [];
    const centerX = canvas.width * 0.25;
    const centerY = -canvas.height * 0.25;
    const radius = canvas.height * rMod;

    for (let i = 0; i < numPoints; i++) {
        const angle = (i / numPoints) * Math.PI * 2;
        const x = centerX + Math.cos(angle) * radius;
        const y = centerY + Math.sin(angle) * radius;
        coordinates.push([x, y]);
    }
    return coordinates;
}