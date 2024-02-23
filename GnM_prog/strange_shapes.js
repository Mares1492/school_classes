let canvas;
let ctx;
let title;

const scale = 1.9

const colors = ["white","blue","bisque","violet","green","pink","yellow","peachpuff","lightgreen"]
const hColors = ["#DC143C","#800020","#C51E3A","red"]

let offset = 0
let offsetX = 0
let offsetY = 0

window.onload = () =>{
    canvas = document.getElementById("canvas")
    ctx = canvas.getContext("2d")
    ctx.scale(scale,scale)
    title = document.getElementById("title")
    canvas.addEventListener('mousedown',drawHearthAtMousePosition)
    let timer = setInterval(()=>{
        init()
        if (offsetY*scale>canvas.height) {
            title.textContent = "This is the end..."
            return clearInterval(timer)
        }
    },10)
};

const getRandomSize = (maxFloored,minCeiled) => Math.floor(Math.random() * (maxFloored - minCeiled) + minCeiled);

const getRandomColor = (colorArr) => colorArr[getRandomSize(0,colorArr.length)]

const drawHearthAtMousePosition = (event) =>{
    const x = event.offsetX;
    const y = event.offsetY;
    drawHearth(x,y,getRandomColor(hColors),5)
}

const drawHearth = (x,y,color=getRandomColor(colors),sizeMod=1) =>{
    const curve = getRandomSize(20,40) * sizeMod
    const curve05 = curve*0.5
    const curve04 = curve*0.4
    const curve025 = curve*0.25
    ctx.fillStyle = color;
    ctx.strokeStyle = 'black';
    ctx.beginPath();
    ctx.moveTo(x, y-curve05); 
    ctx.bezierCurveTo(x, y - curve, x + curve05, y - curve, x + curve05, y - curve04);
    ctx.bezierCurveTo(x + curve05, y - curve025, x, y + curve04, x, y + curve04);
    ctx.bezierCurveTo(x, y + curve04, x - curve05, y - curve025, x - curve05, y - curve04);
    ctx.bezierCurveTo(x - curve05, y - curve, x, y - curve, x, y - curve04);
    ctx.fill()
    ctx.stroke()
    ctx.closePath();
}

const init = () => {
    console.log("FAANG!")
    for (let index = 0; index < 7; index++) {
        ctx.fillStyle = getRandomColor(colors)
        switch (getRandomSize(0,3)) {
            case 0:
                let size = getRandomSize(5,20)
                ctx.beginPath()
                offset += size*2
                ctx.arc(offset+offsetX,(offset/2)+offsetY,size,0, 2 * Math.PI,false)
                ctx.fill()
                ctx.closePath()
                offset -= size*2
                console.log("ARC!")
                break;
            case 1:
                drawHearth((offset/2)+offsetX,(offset/2)+offsetY)
                break
            default:
                ctx.fillRect(offset+offsetX,offset/2+offsetY,getRandomSize(10,50),getRandomSize(10,50))
                console.log("RECT!")
                break;
        }
        console.log("Offset:",offsetX)
    }
    offsetX+=getRandomSize(-5,20)
    if (offsetX*scale>canvas.width) {
        offset = 0
        offsetX = 0
        offsetY += getRandomSize(20,80)
    }
}   


