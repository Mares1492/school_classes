"use strict";;
const gameContainer = document.getElementById("game")
const angles = [0,45,90,135,180,225,270,315];
const nodes = new Map()
var field = []
var foodFoundCounter = 0;
var runs = 0;
var runsData = {
    stepsArr: [],
    totalRuns:0,
    successfulRuns:0,
    bigPileReachedCounter:0,
    smallPileReachedCounter:0
}
var foodPositions = [];
var antStartPos;
var currentSteps = 0;
var stepTimeout = 20;
var isFinishedRun = false;
var antIndex = 0;

//mb add weight to decision
var getNewRandomAngle = ()=> Math.floor(Math.random() * (angles.length-1))

var antData = {
    currentAngleIndex: getNewRandomAngle(), 
    symbol:":",
    leftOverSymbol:".",
    foundFood:false
}

function setStepTimeout(to) {
    stepTimeout = to>0?to:0;
}

function printData() {
    console.log("All runs steps:",runsData.stepsArr)
    console.log("Average steps per run:",runsData.stepsArr.reduce((acc,val)=>acc+val)/runsData.stepsArr.length)
    console.log("Total runs:",runsData.totalRuns)
    console.log("Successful runs:",runsData.successfulRuns)
    console.log("Average success chance per run:",runsData.successfulRuns/runsData.totalRuns)
    console.log("Big piles reached:",runsData.bigPileReachedCounter)
    console.log("Small piles reached:",runsData.smallPileReachedCounter)
}

function generateField(size) {
    clearField();

    for (let row = 0; row < size; row++) {
        const rowElement = document.createElement("div");
        rowElement.classList.add("row");
        field.push([]);

        for (let col = 0; col < size; col++) {
            const colElement = document.createElement("span");
            colElement.classList.add("col");

            colElement.textContent = " ";
            field[row].push(colElement);

            rowElement.appendChild(colElement);
        }

        gameContainer.appendChild(rowElement);
    }
}

function clearField() {
    while (gameContainer.firstChild) {
        gameContainer.removeChild(gameContainer.firstChild);
    }
    if(field.length){
        field = [];
    }
    
}


function updateField(lastPos,antPosition,setLeftOver=false,leftOverSymbol=antData.leftOverSymbol){

    if (field[lastPos.row][lastPos.col].textContent===antData.symbol) {
        if (setLeftOver) {
            field[lastPos.row][lastPos.col].textContent = leftOverSymbol         
        }
        else{
            field[lastPos.row][lastPos.col].textContent = " "
        }
    }
   
    if (field[antPosition.row][antPosition.col].textContent===" " ||field[antPosition.row][antPosition.col].textContent==="") {
        field[antPosition.row][antPosition.col].textContent = antData.symbol;  
        field[antPosition.row][antPosition.col].style.backgroundColor = "#e1bf92"
    }
    
}

function NodeBuilder(nameToSet,initRow,initCol,i){
    this.name = nameToSet;
    this.row = initRow;
    this.col = initCol;
    this.value = 10;
    this.found = false;
    this.foodPileIndex = i;
    nodes.set(this.name,this);

    this.getRandomPointFromObject = (distance = 10) => {
        let rowDistance = Math.ceil(Math.random() * ((distance * 2) + 1)) - distance;
        let leftDistance = Math.abs(rowDistance);
        let colDistance = Math.ceil(Math.random() * ((leftDistance * 2) + 1)) - leftDistance;
        
        console.log(leftDistance, { row: this.row + rowDistance, col: this.col + colDistance }, this.row, this.col);
    
        return { row: this.row + rowDistance, col: this.col + colDistance };
    };

    this.setFade = (fadeInterval,source=undefined) => {
        let interval = setInterval(()=>{
            this.value--;
            if (source!=undefined) {
                source.value++;
            }
            console.log(this.name,"has",this.value," value remaining")
            if (this.value<=0) {
                clearInterval(interval)
                return this.destroy()
            }
        },fadeInterval);
    }

    this.destroy = () => {
        field[this.row][this.col].style.backgroundColor = "gray"
        field[this.row][this.col].textContent = " "
        console.log(this.name,"has been destroyed")
        nodes.delete(this.name)
    }
    
}

function getUniquePositionsDistancedFromObject(obj,amount,distance=10) {
    let positions = []
    let counter = 0;
    for (let i = 0; i < amount; i++) {
        do{
            var newPosition = obj.getRandomPointFromObject(distance)
            counter++  
            if (
                (newPosition.row === antStartPos&&newPosition.col === antStartPos) ||
                (newPosition.row < 0 || newPosition.row >= field.length) ||
                ((newPosition.col < 0 || newPosition.col >= field.length))
            ) {
                continue
            }
        }
        while(positions.some(position=>(position.row === newPosition.row && position.col === newPosition.col)))
        positions.push(new NodeBuilder("food"+(i+1),newPosition.row,newPosition.col,positions.length))
        field[newPosition.row][newPosition.col].style.backgroundColor = "orange"
        field[newPosition.row][newPosition.col].textContent = "o"
    }
    console.log("Number of eterations:",counter)
    console.log(positions)
    return positions
}

function handleTurn(){
    let newIndex = antData.currentAngleIndex + Math.floor(Math.random() * (3) -1)
    if (newIndex<0) {
        newIndex = angles.length-1
    }
    if(newIndex>=angles.length){
        newIndex = 0
    }
    return newIndex
}

function findFood(moves=5,movesPerSearch=100) {
    if (foodFoundCounter>=foodPositions.length) {
        alert("It took "+runs+" runs to find all the food piles");
        return;
    }
    if(moves<=0){
        alert("After "+runs+" runs ant DIDN'T find all the food piles");
        return;
    }
    currentSteps = 0;
    runsData.totalRuns++
    runs++
    console.log("There are",moves,"moves left")
    antData.isFoodFound = false;
    antData.leftOverSymbol = " "
    let destiny = {hasMoved:true}
    let timeouts = [];
    for (let index = 0; index < movesPerSearch; index++) {
        let timeout = setTimeout(()=>{
            if(!destiny.hasMoved || destiny.isFound){
                timeouts.forEach(element => clearTimeout(element));
                if(!destiny.isFound){
                    return moveToPoint(moves,{row:antStartPos,col:antStartPos});
                }
                else{
                    console.log("moving towards food",{col:destiny.col,row:destiny.row})
                    return moveToPoint(moves,{col:destiny.col,row:destiny.row},false); 
                }
            }
            console.log("step")
            currentSteps++;
            destiny = move()
            
            antData.currentAngleIndex = handleTurn();
        },stepTimeout*index)
        timeouts.push(timeout)
    }
}

function getIsFoodReached(antPosition) {
    let food = {found: false}
    let isFound = foodPositions.some(position=>{
        if((Math.abs(position.row-antPosition.row)+Math.abs(position.col-antPosition.col))<=2){
            if (!position.found) {
                position.found = true;
                antData.isFoodFound = true;
                food = position
                if (food.value>10) {
                    runsData.bigPileReachedCounter++;
                }
                else{
                    runsData.smallPileReachedCounter++;
                }
                runsData.successfulRuns++;
                foodFoundCounter++;
                return true;
            }
        }
        return false;
    })
    if (isFound) {
        food.setFade(stepTimeout,nodes.get('base'))
    }

    return food;
}

function handleMoveStep(antPosition,movement,point){
        let isPathToBase = (point.row === antStartPos && point.col === antStartPos)
        let lastPos = {row:antPosition.row,col:antPosition.col}
        let leftOverSymbol = antData.leftOverSymbol
        if ((point.row < antPosition.row)) {
            antPosition.row--
        }
        if ((point.row > antPosition.row)) {
            antPosition.row++
        }
        if ((point.col < antPosition.col)) {
            antPosition.col--
        }
        if ((point.col > antPosition.col)) {
            antPosition.col++
        }
        const antPosToShow = {row:antPosition.row,col:antPosition.col};
        let food = getIsFoodReached(antPosition)
        if (food.found) {
            let isAlreadyHeadingToBaseAfterFindingFood = false;
            console.log("Food is found:",food)
            if (antData.leftOverSymbol === ".") {
                isAlreadyHeadingToBaseAfterFindingFood = true 
            }
            antData.leftOverSymbol = "."
            setTimeout(()=>updateField(lastPos,antPosToShow,isAlreadyHeadingToBaseAfterFindingFood),movement*stepTimeout)
            return food
        }
        setTimeout(()=>updateField(lastPos,antPosToShow,isPathToBase,leftOverSymbol),movement*stepTimeout)
        return {found:false}
         
}

function moveToPoint(moves,point,searchForFood=true){
    console.log("heading towards:",point)
    
    antData.currentAngleIndex = getNewRandomAngle()
    let antPosition = nodes.get("ant") //add antIndex for multiple ants
    let movement = 0
    while ((antPosition.row !== point.row) || (antPosition.col !== point.col)) {
        movement++
        let food = handleMoveStep(antPosition,movement,point);
        if (food.found) {
            return setTimeout(()=>moveToPoint(moves,{row:food.row,col:food.col},false),(movement+1)*stepTimeout)
        }
    }
    console.log("Going back:",(movement+1)*300)
    if (searchForFood) {
        runsData.stepsArr.push(currentSteps)
        return setTimeout(()=>findFood(moves-(antData.isFoodFound?1:0.5)),(movement+1)*stepTimeout)
    }
    else{
        return setTimeout(()=>moveToPoint(moves,{row:antStartPos,col:antStartPos}),(movement+1)*stepTimeout)
    }
}

function move(){
    let antPosition = nodes.get("ant")
    let lastPos = {row:antPosition.row,col:antPosition.col}
    try{
        switch (angles[antData.currentAngleIndex]) {
            case angles[0]:
                antPosition.row--;
                break;
            case angles[1]:
                antPosition.row--;
                antPosition.col++;
                break;
            
            case angles[2]:
                antPosition.col++;
                break;
    
            case angles[3]:
                antPosition.row++;
                antPosition.col++;
                break;
            
            case angles[4]:
                antPosition.row++;
                break;
            
            case angles[5]:
                antPosition.row++;
                antPosition.col--;
                break;
            
            case angles[6]:
                antPosition.col--;
                break;
            
            case angles[7]:
                antPosition.col--;
                antPosition.row--;
                break;
            default:
                console.log("Something went wrong:",angles[antData.currentAngleIndex])
        }
        updateField(lastPos,antPosition)

        let food = getIsFoodReached(antPosition)
        if (food.found) {
            //... food is reached, get back to base
            console.log("Food is found:",food)
            antData.leftOverSymbol = "."
            return {isFound:true,col:food.col,row:food.row,hasMoved:true}
        }
        
    }
    catch(exc){
        console.error("Border Reached")
        
        antPosition.row = lastPos.row
        antPosition.col = lastPos.col
        return {isFound:false,hasMoved:false}
    }
    return {isFound:false,hasMoved:true}
}

function init(runMultiplier = 2,size=26,foodPiles=2) {
    foodFoundCounter = 0;
    runs = 0;
    generateField(size)
    antStartPos = Math.round(field.length/2)
    let ant = spawnAnt()
    let base = spawnBase()
    base.setFade(stepTimeout*10)
    foodPositions = getUniquePositionsDistancedFromObject(base,foodPiles)
    console.log(foodPositions)
    foodPositions[0].value += 10
    findFood(foodPositions.length*runMultiplier)
}

function spawnAnt() {
    antIndex++;
    //ant+antIndex for multiple ants
    return new NodeBuilder("ant",antStartPos,antStartPos)
}

function spawnBase() {
    field[antStartPos][antStartPos].style.backgroundColor = "brown"
    field[antStartPos][antStartPos].textContent = "^"
    return new NodeBuilder("base",antStartPos,antStartPos)
}

function main(spawnInterval=5000,time=10000000) {
    let timeCounter = 0;
    let interval = setInterval(()=>{
        console.log("spawn")
        foodPositions.concat(getUniquePositionsDistancedFromObject(nodes.get("base"),1))
        timeCounter+=spawnInterval
        if (timeCounter>=time || isFinishedRun) {
            console.log("Spawner has been stopped")
            clearInterval(interval)
        }
    },spawnInterval)
    init(100)
}

main()

console.log("Instructions:")
console.log("init()", "to start")
console.log("findFood(foodPositions.length*2)")
console.log("clearField()")
console.log("generateField(size)")
/*  findFood(foodPositions.length*2) -> to find food once
    clearField() -> Clear the field :)
    generateField(size) -> generate the field again

    ↓noAnimationMod ↓
    
    setStepTimeout(0)
    init()
*/




