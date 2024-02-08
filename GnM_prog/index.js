const canvas = document.getElementById("canvas")
const ctx = canvas.getContext("2d")

const colors = ["white","red","blue","bisque","violet"]

let globalTimer = 120

const getRandomSize = (maxFloored,minCeiled) => Math.floor(Math.random() * (maxFloored - minCeiled) + minCeiled);

const getRandomColor = () => colors[getRandomSize(0,colors.length)]

let offset = 0
let offsetX = 0
let offsetY = 0

const init = () => {
    console.log("FAANG!")
    let figure;
    for (let index = 0; index < 7; index++) {
        ctx.fillStyle = getRandomColor()
        switch (getRandomSize(0,2)) {
            case 0:
                offsetY+=100
                ctx.beginPath()
                figure = ctx.arc(offset+offsetX,(offset/2)+offsetY,getRandomSize(5,20),0, 2 * Math.PI,false)
                ctx.fill()
                ctx.closePath()
                console.log("ARC!",offset)
                offsetY-=100
                break;
        
            default:
                figure = ctx.fillRect(offset+offsetX,offset/2,getRandomSize(10,50),getRandomSize(10,50))
                console.log("RECT!",offset)

                break;
        }
        offset+=getRandomSize(-1,5)
    }
    offsetX+=getRandomSize(-5,20)
    if (offset>200) {
        offset = getRandomSize(0,200)
        offsetX = 0 
    }
}   

let timer = setInterval(()=>{
    init()
    globalTimer--
    if (globalTimer<1) {
        return clearInterval(timer)
    }
},500)