#pragma once

class Matrix4x4 
{
	// variables
private:
public:
	float matrix[16] = {0};

	// functions
private:
public:

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

	float& operator[](int index) 
	{
		return matrix[index];
	}
};

typedef Matrix4x4 mat4x4;