let spiralTightness = 5;
let canvas;
let ctx;
let title;
let centerX;
let centerY;
let angle = 0;
let red = 255, green = 255, blue = 255;
let  isGrowing = true;
let points = [];
let isColorGrowing = false;

const getRandomInt = (min,max) => Math.floor(Math.random()*(max-min+1))+min;

const drawStep = () => {
    if (isGrowing) {
        angle+=0.03;
        if (angle>60) {
            isGrowing = false;
            angle = 0;
        }
    }
}

const modifyColor = () => {
    console.log(red,green,blue)
    if (isColorGrowing) {
        if (red < 0) {
            red-=2;
            return;
        }
        if(blue > 0) {
            blue-=2;
            return;
        }
        if (green > 0) {
            green-=2;
            return;
        }
        isColorGrowing = false;
        return;
    }
    if (red < 255) {
        red+=2;
        return;
    }
    if(blue < 255) {
        blue+=2;
        return;
    }
    if (green < 255) {
        green+=2;
        return;
    }
    isColorGrowing = true;
}

const drawSpiral = () => {
    ctx.clearRect(0,0,canvas.width,canvas.height);
    drawStep();
    const newRadius = spiralTightness * angle;
    spiralTightness += 0.005;

    if (isGrowing) {
        const x = centerX + newRadius * Math.cos(angle);
        const y = centerY + newRadius * Math.sin(angle);
        const localRed = red;
        const localGreen = green;
        const localBlue = blue;
        modifyColor();
        points.push({x,y,r:newRadius*0.1,c:`rgb(${localRed} ${localGreen} ${localBlue})`});
    }
    else{
        points.pop();
        if(!points.length){
            isGrowing = true;
            spiralTightness = 1;
        }
    }
    

    for (let i = 0; i < points.length; i++) {
        if (points.length>1 && i>0) {
            ctx.beginPath();
            const prevPoint = points[i-1];
            const point = points[i];
            ctx.moveTo(prevPoint.x,prevPoint.y);
            ctx.lineWidth = point.r;
            ctx.strokeStyle = point.c;
            prevPoint.c = point.c
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
