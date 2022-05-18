xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 28;
 -21.86863;0.01636;-21.86941;,
 21.89381;0.01636;-21.86941;,
 21.89381;0.01636;21.89304;,
 -21.86863;0.01636;21.89304;,
 21.89381;19.96913;-21.86941;,
 21.89381;0.01636;-21.86941;,
 -21.86863;0.01636;-21.86941;,
 -21.86863;24.63338;-21.86941;,
 21.89381;48.66761;17.88163;,
 21.89381;45.01688;21.89304;,
 21.89381;0.01636;-21.86941;,
 21.89381;19.96913;-21.86941;,
 -21.86863;49.39167;21.89304;,
 -21.86863;0.01636;21.89304;,
 21.89381;0.01636;21.89304;,
 21.89381;45.01688;21.89304;,
 -21.86863;49.39167;21.89304;,
 -21.86863;53.20385;17.70431;,
 -21.86863;24.63338;-21.86941;,
 -21.86863;0.01636;-21.86941;,
 -21.86863;53.20385;17.70431;,
 -21.86863;49.39167;21.89304;,
 21.89381;45.01688;21.89304;,
 21.89381;48.66761;17.88163;,
 21.89381;48.66761;17.88163;,
 21.89381;19.96913;-21.86941;,
 -21.86863;24.63338;-21.86941;,
 -21.86863;53.20385;17.70431;;
 
 9;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,2,10;,
 3;8,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 3;16,19,3;,
 4;20,21,22,23;,
 4;24,25,26,27;;
 
 MeshMaterialList {
  4;
  9;
  3,
  1,
  1,
  1,
  1,
  0,
  0,
  2,
  2;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\building500.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\building501.jpg";
   }
  }
  Material {
   0.599200;0.599200;0.599200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\concrete.jpg";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  8;
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.040329;0.403423;0.914125;,
  -1.000000;0.000000;0.000000;,
  0.000000;-0.000000;1.000000;,
  0.073732;0.737557;0.671247;,
  0.086093;0.807771;-0.583175;;
  9;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  3;2,2,2;,
  4;3,5,5,3;,
  4;4,4,4,4;,
  3;4,4,4;,
  4;6,3,3,6;,
  4;7,7,7,7;;
 }
 MeshTextureCoords {
  28;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.725870;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.661780;,
  0.908340;0.331570;,
  1.000000;0.381730;,
  0.000000;1.000000;,
  0.000000;0.725870;,
  1.000000;0.321620;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.381730;,
  0.000000;0.321620;,
  0.095720;0.269250;,
  1.000000;0.661780;,
  1.000000;1.000000;,
  0.213704;0.964216;,
  0.179902;0.904468;,
  1.023447;0.453799;,
  1.055818;0.511017;,
  1.055818;0.511017;,
  1.545447;1.376464;,
  0.701148;1.825802;,
  0.213704;0.964216;;
 }
}
