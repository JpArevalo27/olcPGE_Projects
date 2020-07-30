ArrayList<Firework> fireworks; //<>// //<>// //<>//
PVector gravity;
//to change the screen size please modify the random initially velocity and 
// multiplier factor in the Particle class, as well as the stroke weights 
//in the Show() function in the same class. Also, change the number of 
//particles that explote in the for loop inside the Explode() function in 
//Firework

void setup() {
    //size(400, 300);
    fullScreen();
    colorMode(HSB);
    gravity = new PVector(0, 0.2);
    stroke(255);
    strokeWeight(4);
    fireworks = new ArrayList<Firework>();
    background(0);
}

void draw() {
    colorMode(RGB);
    background(0, 255, 0, 25);
    if (random(1) < 0.3 && fireworks.size() < 25) {
        Firework f = new Firework();
        fireworks.add(f);
    }
    for (int i = fireworks.size() - 1; i >= 0; i--) {
        fireworks.get(i).Update(gravity);
        fireworks.get(i).Show();
        if(fireworks.get(i).isDone())
            fireworks.remove(i);
    }
    
    println("the size of fireworks is: " + fireworks.size());
}
