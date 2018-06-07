# Ray_Tracer

### **Complilation**

 • Firstly, one needs to compile the source code. That task was simplified with the aid of a Makefile: in a console from within the project's root folder, simply type:
 
    ~$ make

### **Execution**

 • To run the binary, specific inputs are expected. Input examples are suplied in the ./bin folder. From the ./bin folder, run:

    ~$ ./rt <camera_file> <scene_file> ./<output_img>.ppm

 • The following code should generate a "myTestImage.ppm" file in ./bin/img, based on the sample _scene_ and _camera_ files provided:

    ~$ ./rt SampleCamera.in SampleScene.in ./myTestImage.ppm

 • Here, <camera_file> and <scene_file>, located in your ./bin folder, must have a specific format that is assumed by the program in order to run correctly:


##### A) The <camera_file> contains all the camera parameters: its position, rotation and resolution. It must follow the format discribed on the table's left column, which will be interpretated accordingly:

          Format          |     Corresponding Interpretation
    ______________________________________________________________________________________________________
    | int int             |    Width Height     =   resolution of the camera                             |
    | float float float   |   X     Y     Z     =   position of the camera                               |
    | float float float   |   X     Y     Z     =   position of the target the camera is looking towards |
    | float float float   |   X     Y     Z     =   vector representing the upwards direction            |
    ______________________________________________________________________________________________________

##### B) The <scene_file> contains all the objects in the scene (spheres and sources) as well the background colour. It must follow the format discribed on the table's left column, which will be interpretated accordingly:

                 Format                   |     Corresponding Interpretation
    ______________________________________________________________________________________________________
    | int[0-255] int[0-255] int[0-255]    | Red  Green  Blue    = background color                       |
    | uint uint                           | #spheres #sources   = number of objects in the scene         |
    ______________________________________________________________________________________________________

• For each sphere in [1,..., #spheres], four lines will be read:

              Format                    |     Corresponding Interpretation
    ______________________________________________________________________________________________________
    | float                             |         Radius                = radius of the sphere           |
    | float float float float           | Ka Kd Ks SH MET               = reflection coefficients        |
    | int[0-255] int[0-255] int[0-255]  |  Red  Green  Blue             = color of the sphere            |
    | float float float                 |   X     Y     Z               = center of the sphere           |
    ______________________________________________________________________________________________________

###### REFLECTION COEFFICIENTS:
######  •_[Ka]  AMBIENT REFLECTION COEFFICIENT_: determines how much the material shall be influenced by ambient light (light coming equally from all directions).
######  •_[Kd]  DIFFUSE REFLECTION COEFFICIENT_: diffuse surfaces are microscopically irregular, and scatter reflected light (see Lambertian reflectance).
######  •_[Ks]  SPECULAR REFLECTION COEFFICIENT_: specular surfaces are smooth and possess close to mirror-like behaviour.
######  •_[SH]  SHININESS REFLECTION COEFFICIENT_: materials have smaller yet more instense specular reflections. 
######  •_[MET] METALLICNESS_: increases indirect light reflection. Metallicness, speculariy and shinyness are thus directly related.
          
_[Note that many surfaces have both a diffuse and a specular component.]_

_[For more information on the Reflection Consstants see [Phong Model](https://en.wikipedia.org/wiki/Phong_reflection_model)]_

• For each light source in [1,..., #sources], four lines will be read:

                 Format                 |     Corresponding Interpretation
    ______________________________________________________________________________________________________
    | int[0-255] int[0-255] int[0-255]    | Red Green Blue   =   ambient component of the light          |
    | int[0-255] int[0-255] int[0-255]    | Red Green Blue   =   diffuse component of the light          |
    | int[0-255] int[0-255] int[0-255]    | Red Green Blue   =   specular component of the light         |
    ______________________________________________________________________________________________________


_[Note that spaces between lines is acceptable for both file formats.]_
