﻿#pragma once

class Matrix4x4 
{
	// variables
private:
public:
	float matrix[16] = {0};

	// functions
private:
public:

	// this is purely for testing how opengl sees matrices
	void SetIndex() 
	{
		for (int i = 0; i < 16; i++)
		{
			matrix[i] = (float)i;
		}
	}

	Matrix4x4 Identity()
	{
		Matrix4x4 mat;
		for (int i = 0; i < 16; i += 5) 
		{
			mat.matrix[i] = 1;
		}
		return mat;
	}

	void SetIdentity() { Set(Identity()); }

	void Set(Matrix4x4 mat)
	{
		for (int i = 0; i < 16; i++) 
		{
			matrix[i] = mat.matrix[i];
		}
	}

	void Set(float* mat) 
	{
		for (int i = 0; i < 16; i++)
		{
			matrix[i] = mat[i];
		}
	}

	Matrix4x4 & operator=(const Matrix4x4 &mat) 
	{
		Set(mat);
		return *this;
	}

	Vector4 operator*(Vector4 vec) 
	{
		vec4 rVec = vec4::Zero();

		rVec.x = matrix[0] * vec.x + matrix[1] * vec.y + matrix[2] * vec.z + matrix[3] * vec.w;
		rVec.y = matrix[4] * vec.x + matrix[5] * vec.y + matrix[6] * vec.z + matrix[7] * vec.w;
		rVec.z = matrix[8] * vec.x + matrix[9] * vec.y + matrix[10] * vec.z + matrix[11] * vec.w;
		rVec.w = matrix[12] * vec.x + matrix[13] * vec.y + matrix[14] * vec.z + matrix[15] * vec.w;

		return rVec;
	}

	Matrix4x4 operator*(Matrix4x4 mat)
	{
		float rMat[16];
		float *oMat = mat.matrix;

		// <3 I hate matrices <3
		// ლ(ಠ_ಠლ)

		for (int i = 0; i < 4; i++) 
		{
			for (int j = i*4; j < 4; j ++) 
			{
				rMat[i+j-i*4] = matrix[j] * oMat[i] + matrix[j + 1] * oMat[i + 4] + matrix[j + 2] * oMat[i + 8] + matrix[j + 3] * oMat[i + 12];
			}
		}
		
		//(ง •̀_•́)ง 

		Matrix4x4 nmat;
		nmat.Set(rMat);
		return nmat;
	}

	// ｡◕‿◕｡ ez pz
	Matrix4x4 operator*(float n)
	{
		float rMat[16];
		for (int i = 0; i < 16; i++) 
		{
			rMat[i] = matrix[i] * n;
		}
	}
	Matrix4x4 operator/(float n) 
	{
		float rMat[16];
		for (int i = 0; i < 16; i++)
		{
			rMat[i] = matrix[i] / n;
		}
	}
	Matrix4x4 operator+(float n) 
	{
		float rMat[16];
		for (int i = 0; i < 16; i++)
		{
			rMat[i] = matrix[i] + n;
		}
	}
	Matrix4x4 operator-(float n) 
	{
		float rMat[16];
		for (int i = 0; i < 16; i++)
		{
			rMat[i] = matrix[i] - n;
		}
	}

	Matrix4x4& operator*=(Matrix4x4 mat)
	{
		float rMat[16] = {0};
		for (int i = 0; i < 4; i++) 
		{
			int r = i * 4;
			int c = 0;
		
			rMat[r]   = matrix[r] * mat.matrix[c] + matrix[r + 1] * mat.matrix[c + 4] + matrix[r + 2] * mat.matrix[c + 8] + matrix[r + 3] * mat.matrix[c + 12];
			c++;
			rMat[r+1] = matrix[r] * mat.matrix[c] + matrix[r + 1] * mat.matrix[c + 4] + matrix[r + 2] * mat.matrix[c + 8] + matrix[r + 3] * mat.matrix[c + 12];
			c++;
			rMat[r+2] = matrix[r] * mat.matrix[c] + matrix[r + 1] * mat.matrix[c + 4] + matrix[r + 2] * mat.matrix[c + 8] + matrix[r + 3] * mat.matrix[c + 12];
			c++;
			rMat[r+3] = matrix[r] * mat.matrix[c] + matrix[r + 1] * mat.matrix[c + 4] + matrix[r + 2] * mat.matrix[c + 8] + matrix[r + 3] * mat.matrix[c + 12];
		}

		for(int i = 0; i < 16; i++)
			matrix[i] = rMat[i];

		//for (int i = 0; i < 4; i++)
		//{
		//	for (int j = 0; j < 4; j++)
		//	{
		//		int index = i + j - i * 4;
		//
		//		matrix[index] = matrix[j] * mat.matrix[i] + matrix[j + 1] * mat.matrix[i + 4] + matrix[j + 2] * mat.matrix[i + 8] + matrix[j + 3] * mat.matrix[i + 12];
		//	}
		//}

		return *this;
	}


	float& operator[](int index) 
	{
		return matrix[index];
	}
};

typedef Matrix4x4 mat4x4;