class Firework { //<>//
    Particle firework;
    boolean exploded;
    ArrayList<Particle> parts;
    int hu;

    Firework() {
        hu = (int)random(255);
        firework = new Particle(random(width), height, true, hu);
        exploded = false;
        parts = new ArrayList<Particle>();
    }

    void Update(PVector gravity) {
        if (!exploded) {
            firework.ApplyForce(gravity);
            firework.Update();


            if (firework.vel.y >= 0) {
                exploded = true;
                Explode();
            }
        }
 //<>//
        for (int i = parts.size() - 1; i >= 0; i--) {
            parts.get(i).ApplyForce(gravity);
            parts.get(i).Update();
            if(parts.get(i).isDone()){
                parts.remove(i);
            }
        }
    }

    void Show() {
        if (!exploded) {
            firework.Show();
        }

        for (int i = parts.size() - 1; i >= 0; i--) {
            parts.get(i).Show();
        }
    }

    void Explode() {
        for (int i = 0; i < 200; i++) {
            Particle p = new Particle(firework.pos, false, hu);
            parts.add(p);
        }
    }
    
    boolean isDone(){
        return (exploded && (parts.size() == 0));
    }
}
