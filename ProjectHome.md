**progressive-meshes** is a surface simplification software which produces high-quality approximations of triangle progressive meshes models. It generates progressive meshes models with desired number of mesh faces or compression ratio, and every contraction is recorded in the generated file. Currently only core operators of [.smf](https://people.scs.fsu.edu/~burkardt/data/smf/smf.txt) input file format are supported.

This is a C++ implementation of [Michael Garland](http://graphics.cs.uiuc.edu/~garland/)'s _Surface simplification using quadric error metrics_ and [Hugues Hoppe](http://research.microsoft.com/~hoppe/)'s _Progressive meshes_. This software runs slower than Garland's [Qslim](http://graphics.cs.uiuc.edu/~garland/software/qslim.html), but the results are somehow better in details. Since every contraction is recorded, further usage of the generated .pm file could be extended, for example, building level-of-detail models or 3D streaming.

Credit goes to [SU Tao](http://taosu.net) for GUI.

### Installation ###

http://hezhao.net/projects/progressive-meshes/