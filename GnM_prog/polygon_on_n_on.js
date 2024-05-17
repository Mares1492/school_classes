let canvas;
let ctx;
let title;
let isStopped = false;

const scale = 2;
const colors = ['yellow','red',"blue",'lime','purple','pink','green','white'];


const getRandomInt = (min,max) => Math.floor(Math.random()*(max-min+1))+min;
const getRandomColor = () => colors[getRandomInt(0,colors.length)]
const getRandomColors = () => {
    const copy = [...colors]
    const colorIndex = getRandomInt(0,copy.length);
    const color = copy[colorIndex];
    copy.splice(colorIndex,1);
    const color2 = copy[getRandomInt(0,copy.length)]
    return [color,color2];
}
let angle = getRandomInt(0,360);
let numPoints = getRandomInt(3,12);
let outerRadius = getRandomInt(50,150);
let innerRadius = outerRadius / 2;
let lineWidth = Math.random() * (outerRadius / 10);
let x;
let y;
let fillStyle;
let strokeStyle;


const drawStar = (
    centerX,
    centerY,
    numPoints,
    innerRadius,
    outerRadius,
    startAngle,
    fillStyle,
    strokeStyle,
    lineWidth
) => {
    let radians = startAngle * Math.PI / 180  || 0;
    let step = Math.PI / numPoints, hyp, x, y;
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    ctx.strokeStyle = strokeStyle;
    ctx.fillStyle = fillStyle;
    ctx.lineWidth = lineWidth;
    
    ctx.beginPath();
    for (let i =0,len= 2 * numPoints; i <len; i++) {
        hyp = i & 1 ? innerRadius : outerRadius;
        x = centerX + Math.cos(radians) * hyp;
        y = centerY +Math.sin(radians) * hyp;
        radians+=step;
        ctx.lineTo(x, y);
    }
    ctx.closePath();
    ctx.fill();
    ctx.stroke();
    return startAngle + 1;
}
const init = () => {
    title.textContent = "This is the process!";
    let interval = setInterval(()=>{
        if(isStopped){
            title.textContent = "This is the end...";
            return clearInterval(interval);
        }
        angle = drawStar(
            x,y,numPoints,
            innerRadius,outerRadius,angle,
            fillStyle,strokeStyle,lineWidth
        )
    },30)
}

const setup = () => {
    numPoints = getRandomInt(3,12);
    outerRadius = getRandomInt(50,150);
    innerRadius = outerRadius / 2;
    lineWidth = Math.random() * (outerRadius / 5);
    [fillColor,strokeColor] = getRandomColors()
    fillStyle = fillColor;
    strokeStyle = strokeColor;
}

window.onload = () =>{
    canvas = document.getElementById("canvas");
    ctx = canvas.getContext("2d");
    title = document.getElementById("title");
    ctx.scale(scale,scale);
    x = (canvas.width*0.5)/scale;
    y = (canvas.height*0.5)/scale;
    canvas.addEventListener("click",()=>{
        isStopped = !isStopped
        if (!isStopped) {
            init();
        }
    })
    canvas.addEventListener("dblclick",()=>{
        setup();
        init();
    })
    setup();
    init();
}



