//1. Создать список из 10 пунктов, в скрипте реализовать функцию, которая будет поочередно
//с верху вниз менять задний фон пунктов меню и при достижении конца начинать сначала.
//Нужно менять не только задний фон, но и сам цвет фона. То есть на каждом пункту меню будет разный цвет.
//Все остальные пункты, на которых не происходит замена в данный момент, должны быть одного цвета.

var colors = ["red", "yellow", "green", "blue", "navy", "black", "orange", "violet", "grey", "red"];
var i = 0;

var timer = setInterval(function(){
    if(i > 0 && i <= list.length){
        ChangeColor(i-1, "none");
        list[i-1].style.color = "black";
    }
    if(i >= 0 && i < list.length){
        ChangeColor(i, colors[i]);
    }
    if(i == list.length){
        i = -1;
        //clearInterval(timer);
    }
    i++;
}, 500);

var list = document.getElementsByTagName("li");

function ChangeColor(n, color){
    style = list[n].style;
    style.background = color;
    style.color = "white";
}

//##########################################################

//2. Реализовать функцию движения кнопки по экрану. Кнопка или див должна двигаться по
// периметру экрана кругами, при этом каждые 2 сек менять свой бэкграунд.

/*var colors = ["red", "yellow", "green", "blue", "cyan", "pink", "orange", "violet", "grey", "black"];
element = document.getElementById("figure");
element_style = document.getElementById("figure").style;
var window_width = window.screen.width;
var window_height = window.screen.height;
var i = 0;
var direction;

function ChangeColor(color){
    element_style.background = color;
}

function ChangePosition(direction){
    switch (direction){
        case "left":
            element_style.left = element.offsetLeft + 50 + 'px';
        break;
        case "down":
            element_style.top = element.offsetTop + 50 + 'px';
        break;
        case "right":
            element_style.left = element.offsetLeft - 50 + 'px';
        break;
        case "up":
            element_style.top = element.offsetTop - 50 + 'px';
        break;
    }
}

var timer = setInterval(function(){
    if(i == colors.length){
        i = 0;
    }
   ChangeColor(colors[i]);
    i++;
}, 2000);

var move = setInterval(function(){
    if(element.offsetTop == 10 && element.offsetLeft <= window_width - element.style.width - 100){
        direction = "left";
    }
    else if(element.offsetLeft >= window_width - element.style.width - 100 && element.offsetTop <= window_height - element.style.height - 210){
        direction = "down";
    }
    else if(element.offsetTop >= window_height - element.style.height - 210 && element.offsetLeft >= window_width - element.style.width - 210){
        direction = "right";
    }
    else if(element.offsetTop >= window_height - element.style.height - 210 && element.offsetLeft <= 10){
        direction = "up";
    }
    ChangePosition(direction);
},200);*/

//##################################################################################################################

//3. Сделать таблицу котировок биржи. Таблица 10х10 элементов, в которой с определенной частотой
//меняются показатели. Если новый показатель больше старого, то задний фон зеленый, меньше красный
//не поменялся серый. Менять не все показатели, а выборочно несколько до 5 штук. В заголовке таблицы
//название фирм. Частоту смены показателей вводит пользователь, через промпт.

//var table = document.all.tab;
//var periodicity = prompt("Частота смены показателей", 200);
//var row, col, value, count;
//
//
//for(var i = 1; i < 11; i++){
//    for(var k = 0; k < 10; k++){
//        value = (Math.random() * 10).toFixed(4);
//        table.rows[i].cells[k].innerHTML = value;
//    }
//}
//
//var timer = setInterval(function(){
//    ChangeValues();
//}, periodicity);
//
// function ChangeValues(){
//     count = Math.floor(Math.random() * 5) + 1;
//     for(var i = 0; i < count; i++){
//         row = Math.floor(Math.random() * (10)) + 1;        // 1-10
//         col = Math.floor(Math.random() * 10);           // 0-9
//         value = (Math.random() * 10).toFixed(4);
//
//         if(table.rows[row].cells[col].innerHTML < value){
//             table.rows[row].cells[col].style.background = "green";
//         }
//         else if(table.rows[row].cells[col].innerHTML > value){
//             table.rows[row].cells[col].style.background = "red";
//         }
//         else{
//             table.rows[row].cells[col].style.background = "grey";
//         }
//         table.rows[row].cells[col].innerHTML = value;
//     }
// }

//#################################################################################