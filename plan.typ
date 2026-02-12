#set page(height: auto)
#set text(font: "Linux Libertine", size: 11pt)

#align(center)[
  #block(inset: 10pt, fill: rgb("#eeeeee"), radius: 5pt)[
    #text(size: 24pt, weight: "bold")[The Ray Tracer's Journey] \
    #text(size: 12pt, style: "italic")[From Pixels to Photorealism]
  ]
]

== The Vision
Ray tracing is not about drawing shapes; it is about *simulating physics*. You are building a digital camera that shoots millions of "light" rays into a virtual scene to see what they hit.

== Phase 1: The World of Geometry
We define where things are and how they interact mathematically.
- *The Viewport:* Your "window" into the 3D world.
- *The Hittable List:* A manager that holds all your objects and finds the closest intersection for every ray.
- *The Plane:* A flat, infinite surface. Placing a sphere on a plane is the moment your project stops being a "graph" and starts being a "scene."

== Phase 2: Material Science
This is where objects gain personality. We use the *Surface Normal* to decide how light bounces.
- *Matte (Lambertian):* Light scatters randomly. This gives you soft, realistic shadows.
- *Metal:* Rays reflect like a mirror. You will see the world "inside" the sphere.
- *Glass (Dielectrics):* Rays bend (refract). This is the "wow" moment of ray tracing.

== Phase 3: Recursive Bouncing
Currently, your rays "die" when they hit a sphere. In this phase, we let them live:
$ P(t) = A + t B $
When a ray hits a mirror, we calculate a *new* ray and shoot it again. If a pixel looks at a mirror, the mirror looks at the floor, and the floor looks at the sky, the final pixel color is a blend of all three.

== Phase 4: Anti-Aliasing
Instead of shooting 1 ray per pixel, we shoot 100 rays with tiny random offsets.
$ "Color" = 1/N sum_(i=1)^N "Sample"_i $
This turns jagged, "pixelated" edges into smooth, photographic curves.

#align(center)[
  #box(stroke: 1pt + gray, inset: 10pt)[
    *Your Current Milestone:* \
    You have mastered the Sphere and the Ray. \
    Next stop: *The Hittable List and the Floor.*
  ]
]
