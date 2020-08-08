class Particle { //<>// //<>// //<>//
    PVector pos, vel, acc;
    boolean firework;
    int lifespan, hu;
    
    Particle() {
        pos = new PVector(0.0, 0.0);
        vel = new PVector(0.0, 0.0);
        acc = new PVector(0.0, 0.0);
        firework = false;
        lifespan = 255;
    }

    Particle(float x, float y, boolean firework_, int hu_) {
        firework = firework_;
        hu = hu_;
        lifespan = 255;
        pos = new PVector(x, y);

        if (firework)
            vel = new PVector(random(-10, 10), random(-25, -8));
        else
            PVector.random2D(vel);

        acc = new PVector(0.0, 0.0);
    }

    Particle(PVector pos_, boolean firework_, int hu_) {
        hu = hu_;
        lifespan = 255;
        firework = firework_;
        pos = pos_.copy();
        if (firework)
            vel = new PVector(random(-10, 10), random(-12, -8));
        else {
            vel = new PVector();
            vel = PVector.random2D();
            vel.mult(random(4, 12));
        }
        acc = new PVector(0.0, 0.0);
    }

    void ApplyForce(PVector force) {
        acc.add(force);
    }

    void Update() {
        vel.add(acc);
        if (!firework) {
            vel.mult(0.95);
            lifespan -= 4;
        }
        pos.add(vel);
        acc.mult(0);
    }

    void Show() {
        colorMode(HSB);
        if (!firework) {
            strokeWeight(8);
            stroke(hu, 255, 255, lifespan);
        } else {
            strokeWeight(12);
            stroke(hu, 255, 255);
        }
        point(pos.x, pos.y);
    }

    void SetVelocity(float x, float y) {
        vel = new PVector(x, y);
    }
    
    boolean isDone(){
        return (lifespan < 0);
    }
}
