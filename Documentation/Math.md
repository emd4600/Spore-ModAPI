@page Math Math, transforms and random numbers
@brief A quick overview of the main functionalities of the Math namespace

@section Math-Vectors Vectors

In the `Math` module, **vectors** are collection of 2, 3 or 4 float numbers: *x*, *y*, *z*, *w*. Note that this is not related to the `vector` container in C++.
`Vector2` represents a direction in 2D-space, whereas `Vector3` represents a direction in 3D-space. You can declare the values of a vector by using the 
constructor, or using `{ }`:
~~~~{.cpp}
// Using the constructor:
Vector2 v = Vector2(10, 20);

// Using {}
Vector3 v2 = { -0.4, 0, 1.75 };

// You can access the individual elements:
float number = v.x + v2.z * v.y;
~~~~

There are basic arithmetical operations between vectors of the same type; you cannot operator with vectors of different dimensions.
~~~~{.cpp}
Vector3 v1 = { 0.1, 3, 2 };
Vector3 v2 = { -0.4, 0, 1.75 };

// You can add/subtract vectors and multiply/divide them with scalars
auto v = (v1 + v2) / 2.0;
~~~~

There are also 2 operations specific to vector mathematics:
 - `Length()` returns the length of the vector, also known as the magnitude. This is the square root of the sum of its components squared.
 - `Dot(v)` is the dot product with the vector `v`. This can be used to know the angle between two vectors, and whether they are perpendicular.
 
Additionally, 3-dimensional vectors have an extra operation, the cross product `Cross(v)`. This will return another vector that is perpendicular to
both vectors.
 
~~~~{.cpp}
// Example: get the distance between two creatures
float dist = (creature2->GetPosition() - creature1->GetPosition()).Length();
~~~~

@section Math-Matrix Matrices

A matrix is a grid of floating point numbers, organized in rows and columns. The `Math` module only supports two types of matrices:
 - `Matrix3`, which is a *3x3* matrix (3 rows, 3 columns, in total 9 values)
 - `Matrix4`, which is a *4x4* matrix (4 rows, 4 columns, in total 16 values)
 
*3x3* matrices are usually used to represent rotations, whereas *4x4* matrices are used to represent more general transformations (i.e. rotation,
translation and scaling). The default state of a matrix, that represents no transformation, is the *identity* matrix.

~~~~{.cpp}
Matrix3 m = Matrix3().SetIdentity();
~~~~

Matrices can be multiplied with vectors to transform that vector. Similarly, matrices can be umltiplied with other matrices to chain transformations.
Keep in mind that matrix product is not commutative, that is `A*B != B*A`. Since working with rotation matrices is not intuitive, there's a method
to transform *euler* angles into a rotation matrix. Keep in mind that the angles must be in *radians*:

~~~~{.cpp}
// Rotate the vector 'v' 90º around the Y axis

Matrix3 m = Matrix3::FromEuler({ 0, Math::ToRadians(90), 0 });
Vector3 result = m * v;
~~~~

@section Math-Transform Transforms

Many Spore objects, such as models and effects, use the `Transform` class to define their transformations in the 3D space. A `Transform` is a 
combination of a **position** (*offset*), **rotation** and **scale**.

```cpp
Transform t;
// You can chain transformations
t.SetScale(2.0).SetOffset(0, 0, -5);

// You can rotate using euler angles, quaternions, or rotation matrices
t.SetRotation({ 0, Math::ToRadians(90), 0 });
```

You can also convert a Transform into its Matrix4 representation, which can be used to apply the transformation to vectors.

@section Math-Colors Colors

Colors in Spore are represented by 3 different structures: `Color`, `ColorRGB` and `ColorRGBA`.
`ColorRGB` is equivalent to `Vector3`, but its members are *r* (red), *g* (green), *b* (blue). The values usually are
between 0.0 and 1.0, but they can go higher. 

`ColorRGBA` is equivalent to `Vector4`. It's very similar to the RGB version, but this has an extra member: *a* (alpha, that is, opacity).
Alpha always goes between 0.0 (transparent) and 1.0 (opaque), and it's 1.0 by default.

`Color` is an integer that represents an RGBA color. It also has *r*, *g*, *b*, *a* values, but here they are integers from 0 to 255.

There's an extra type of color, `ColorHSV`. Instead of using the common RGB channels, this one uses *hue*, *saturation* and *value*. The methods
`Math::RGBtoHSV()` and `Math::HSVtoRGB()` can be used to convert from one type to another.


@section Math-Random Random numbers

The `Math` module includes function to generate pseudo-random numbers. The reason they are called pseudo-random is because they are not completely 
aleatory: they are generated based on a *seed*; when the seed is the same, the generated numbers can be predicted.

Spore has a generic random number generator, which uses the game time as *seed*; this ensures that every time you open the game the seed is different.
[Math::rand(range)](@ref Math::rand()) will generate a random integer number between 0 and `range`. There are also methods to generate random float numbers:
`Math::randf()` will generate a number between 0.0 and 1.0; `Math::randf(minValue, maxValue)` generates a number getween `minValue` and `maxValue`.

~~~~{.cpp}
// Example: generate a random vector with values from -7 to 7
Vector3 v = { Math::randf(-7, 7), Math::randf(-7, 7), Math::randf(-7, 7) };
~~~~

In some cases, it's useful to use a fixed `seed`. For example, if you generate a planet with random effects, you will want to keep the same seed to 
have the same results. You can create your own RNG:

~~~~{.cpp}
RandomNumberGenerator rng(6817293);
int value = rng.RandomInt();
~~~~