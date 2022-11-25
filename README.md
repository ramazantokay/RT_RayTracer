# RT RayTracer

This is a basic multi-threaded Ray Tracer implementation for CENG477 Computer Graphics course. It is fast and has OOP features.

### Some of the properties of the Ray Tracer as follows:
	
<ul>  
  <li>Having strong OOP features</li>
  <li>Multi-threaded rendering </li>
	<li>Parsing XML scene files and rendering images in PPM format</li>
	<li>An extensible abstract shape intersection base class called Shape, and derived Sphere, Triangle, and Mesh classes</li>
	<li>Point and Ambient Lights</li>
	<li>Cameras, Image planes</li>
	<li>Shading models
    <ul>
      <li>Diffuse Shading</li>
      <li>Ambient Shading</li>
      <li>Bling-Phong (Specular) Shading</li>
     </ul>
   </li>
	<li>Mirrorness</li>
	<li>Shadows</li>
</ul>

### QuickStart

Download the repository

``` 
git clone https://github.com/ramazantokay/RayTracer.git
```
and run the following command on the terminal
```
make all
```
then, you can use the RayTracer with this command

```
./raytracer <sample_scenes/scene_file.xml>
```
It will render the scene and save it in its current directory with ppm format.

# My Example scenes

**David Statue**

![David](/assets/david.png)

**Utah Teapot METU CENG compositon**

![Utah Teapot Composition](/assets/UtahTeapotMugCENG.png)

**Utah Teapot Reflection**

![Utah Teapot Reflection](/assets/UtahTeapotReflection.png)

# Some provided scene 

**Dragon**

![Dragon](/assets/dragon_lowres.png)

**Marbles**

![Marbles](/assets/marbles.png)

**Mirror Spheres**

![Mirror Spheres](/assets/mirror_spheres.png)
