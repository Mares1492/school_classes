const spiralTightness = 10;

let canvas;
let ctx;
let title;
let centerX;
let centerY;
let angle = 0;
let  isGrowing = true;
let points = [];

const getRandomInt = (min,max) => Math.floor(Math.random()*(max-min+1))+min;

const drawStep = () => {
    if (isGrowing) {
        angle+=0.1;
        if (angle>80) {
            isGrowing = false;
            angle = 0;
        }
    }
}

const drawSpiral = () => {
    ctx.clearRect(0,0,canvas.width,canvas.height);
    ctx.strokeStyle = "white";
    drawStep();
    const newRadius = spiralTightness * angle;

    if (isGrowing) {
        const x = centerX + newRadius * Math.cos(angle);
        const y = centerY + newRadius * Math.sin(angle);
        points.push({x,y,c:`rgb(${getRandomInt(0,255)} ${getRandomInt(0,255)} ${getRandomInt(0,255)})`});
    }
    else{
        points.pop();
        if(!points.length){
            isGrowing = true;
        }
    }
    

    for (let i = 0; i < points.length; i++) {
        if (points.length>1 && i>0) {
            ctx.beginPath();
            const prevPoint = points[i-1];
            const point = points[i];
            ctx.moveTo(prevPoint.x,prevPoint.y);
            ctx.lineWidth = i*0.02;
            ctx.strokeStyle = point.c;
            ctx.lineTo(point.x,point.y);ctx.stroke();    
            ctx.closePath();   
        }
    }



    requestAnimationFrame(drawSpiral);
}

window.onload = () =>{
    canvas = document.getElementById("canvas");
    ctx = canvas.getContext("2d");
    title = document.getElementById("title");
    title.textContent = "This is the spiral process";
    centerX = canvas.width*0.5;
    centerY = canvas.height*0.5;
    drawSpiral();
}
