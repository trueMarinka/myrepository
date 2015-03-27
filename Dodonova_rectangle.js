/**
 * Created by Маринка on 24.03.2015.
 */
function Point(x, y){
    this.x = x;
    this.y = y;
    this.Show = function(){
        alert("x = " + this.x + " y = " + this.y)
    }
}


function Rectangle(width, height) {
    this.left_top = new Point(0,0);
    this.right_top = new Point(width,0);
    this.left_bottom = new Point(0,height);
    this.right_bottom = new Point(width,height);

    this.Change = function(a, b, c, d) {
        this.left_top  = a;
        this.right_top = b;
        this.left_bottom = c;
        this.right_bottom = d;
    };

    this.Show = function(){
        this.left_top.Show();
        this.right_top.Show();
        this.left_bottom.Show();
        this.right_bottom.Show();
    };
}
var rec = new Rectangle(20, 10);
var a = new Point(5, 5);
var b = new Point(10, 5);
var c = new Point(5, 10);
var d = new Point(10, 10);
rec.Change(a, b, c, d);
rec.Show();