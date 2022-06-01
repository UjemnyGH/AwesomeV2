#pragma once

#include "e_Core.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <bit>
#include <limits>
#include <cstdint>

namespace aws
{
    namespace math
    {
        /**
         * @brief Awesome vector type
         * 
         */
        struct Aws_Vector
        {
            float x = 0.0f, y = 0.0f, z = 1.0f, w = 1.0f;

            Aws_Vector() = default;
            Aws_Vector(float _x) : x(_x) {}
            Aws_Vector(float _x, float _y) : x(_x), y(_y) {}
            Aws_Vector(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
            Aws_Vector(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}

            static Aws_Vector changeS(float _val) { return Aws_Vector(_val); }
            static Aws_Vector changeS(glm::vec2 _val) { return Aws_Vector(_val.x, _val.y); }
            static Aws_Vector changeS(glm::vec3 _val) { return Aws_Vector(_val.x, _val.y, _val.z); }
            static Aws_Vector changeS(glm::vec4 _val) { return Aws_Vector(_val.x, _val.y, _val.z, _val.w); }

            Aws_Vector change(float _val) { return Aws_Vector(_val); }
            Aws_Vector change(glm::vec2 _val) { return Aws_Vector(_val.x, _val.y); }
            Aws_Vector change(glm::vec3 _val) { return Aws_Vector(_val.x, _val.y, _val.z); }
            Aws_Vector change(glm::vec4 _val) { return Aws_Vector(_val.x, _val.y, _val.z, _val.w); }

            static float changeV1S(Aws_Vector _val) { return _val.x; }
            static glm::vec2 changeV2S(Aws_Vector _val) { return glm::vec2(_val.x, _val.y); }
            static glm::vec3 changeV3S(Aws_Vector _val) { return glm::vec3(_val.x, _val.y, _val.z); }
            static glm::vec4 changeV4S(Aws_Vector _val) { return glm::vec4(_val.x, _val.y, _val.z, _val.w); }

            float changeV1() { return this->x; }
            glm::vec2 changeV2() { return glm::vec2(this->x, this->y); }
            glm::vec3 changeV3() { return glm::vec3(this->x, this->y, this->z); }
            glm::vec4 changeV4() { return glm::vec4(this->x, this->y, this->z, this->w); }

            bool operator<(Aws_Vector& vec) {
                return this->x * this->y * this->z * this->w / 4.0f < vec.x * vec.y * vec.z * vec.w / 4.0f;
            }

            bool operator>(Aws_Vector& vec) {
                return this->x * this->y * this->z * this->w / 4.0f > vec.x * vec.y * vec.z * vec.w / 4.0f;
            }

            Aws_Vector operator+(const Aws_Vector& vec) { 
                this->x += vec.x;
                this->y += vec.y;
                this->z += vec.z;
                this->w += vec.w;

                return *this;
            }

            Aws_Vector operator-(const Aws_Vector& vec) {
                this->x -= vec.x;
                this->y -= vec.y;
                this->z -= vec.z;
                this->w -= vec.w;

                return *this;
            }

            Aws_Vector operator*(const Aws_Vector& vec) {
                this->x *= vec.x;
                this->y *= vec.y;
                this->z *= vec.z;
                this->w *= vec.w;

                return *this;
            }

            Aws_Vector operator/(const Aws_Vector& vec) {
                this->x /= vec.x;
                this->y /= vec.y;
                this->z /= vec.z;
                this->w /= vec.w;

                return *this;
            }

            const Aws_Vector operator+(Aws_Vector& vec) {
                this->x += vec.x;
                this->y += vec.y;
                this->z += vec.z;
                this->w += vec.w;

                return *this;
            }

            const Aws_Vector operator-(Aws_Vector& vec) {
                this->x -= vec.x;
                this->y -= vec.y;
                this->z -= vec.z;
                this->w -= vec.w;

                return *this;
            }

            const Aws_Vector operator*(Aws_Vector& vec) {
                this->x *= vec.x;
                this->y *= vec.y;
                this->z *= vec.z;
                this->w *= vec.w;

                return *this;
            }

            const Aws_Vector operator/(Aws_Vector& vec) {
                this->x /= vec.x;
                this->y /= vec.y;
                this->z /= vec.z;
                this->w /= vec.w;

                return *this;
            }

            Aws_Vector operator+=(const Aws_Vector& vec) {
                this->x += vec.x;
                this->y += vec.y;
                this->z += vec.z;
                this->w += vec.w;

                return *this;
            }

            Aws_Vector operator-=(const Aws_Vector& vec) {
                this->x -= vec.x;
                this->y -= vec.y;
                this->z -= vec.z;
                this->w -= vec.w;

                return *this;
            }

            Aws_Vector operator*=(const Aws_Vector& vec) {
                this->x *= vec.x;
                this->y *= vec.y;
                this->z *= vec.z;
                this->w *= vec.w;

                return *this;
            }

            Aws_Vector operator/=(const Aws_Vector& vec) {
                this->x /= vec.x;
                this->y /= vec.y;
                this->z /= vec.z;
                this->w /= vec.w;

                return *this;
            }

            const Aws_Vector operator+=(Aws_Vector& vec) {
                this->x += vec.x;
                this->y += vec.y;
                this->z += vec.z;
                this->w += vec.w;

                return *this;
            }

            const Aws_Vector operator-=(Aws_Vector& vec) {
                this->x -= vec.x;
                this->y -= vec.y;
                this->z -= vec.z;
                this->w -= vec.w;

                return *this;
            }

            const Aws_Vector operator*=(Aws_Vector& vec) {
                this->x *= vec.x;
                this->y *= vec.y;
                this->z *= vec.z;
                this->w *= vec.w;

                return *this;
            }

            const Aws_Vector operator/=(Aws_Vector& vec) {
                this->x /= vec.x;
                this->y /= vec.y;
                this->z /= vec.z;
                this->w /= vec.w;

                return *this;
            }
        };

        /**
         * @brief Awesome double vector type
         *
         */
        struct Aws_DVector
        {
            double x = 0.0, y = 0.0, z = 1.0, w = 1.0;

            Aws_DVector() = default;
            Aws_DVector(float _x) : x(_x) {}
            Aws_DVector(float _x, float _y) : x(_x), y(_y) {}
            Aws_DVector(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
            Aws_DVector(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}

            static Aws_DVector changeS(double _val) { return Aws_DVector(_val); }
            static Aws_DVector changeS(glm::dvec2 _val) { return Aws_DVector(_val.x, _val.y); }
            static Aws_DVector changeS(glm::dvec3 _val) { return Aws_DVector(_val.x, _val.y, _val.z); }
            static Aws_DVector changeS(glm::dvec4 _val) { return Aws_DVector(_val.x, _val.y, _val.z, _val.w); }

            Aws_DVector change(double _val) { return Aws_DVector(_val); }
            Aws_DVector change(glm::dvec2 _val) { return Aws_DVector(_val.x, _val.y); }
            Aws_DVector change(glm::dvec3 _val) { return Aws_DVector(_val.x, _val.y, _val.z); }
            Aws_DVector change(glm::dvec4 _val) { return Aws_DVector(_val.x, _val.y, _val.z, _val.w); }

            static double changeV1S(Aws_DVector _val) { return _val.x; }
            static glm::dvec2 changeV2S(Aws_DVector _val) { return glm::dvec2(_val.x, _val.y); }
            static glm::dvec3 changeV3S(Aws_DVector _val) { return glm::dvec3(_val.x, _val.y, _val.z); }
            static glm::dvec4 changeV4S(Aws_DVector _val) { return glm::dvec4(_val.x, _val.y, _val.z, _val.w); }

            double changeV1() { return this->x; }
            glm::dvec2 changeV2() { return glm::dvec2(this->x, this->y); }
            glm::dvec3 changeV3() { return glm::dvec3(this->x, this->y, this->z); }
            glm::dvec4 changeV4() { return glm::dvec4(this->x, this->y, this->z, this->w); }

            Aws_DVector operator+(const Aws_DVector& vec) {
                this->x += vec.x;
                this->y += vec.y;
                this->z += vec.z;
                this->w += vec.w;

                return *this;
            }

            Aws_DVector operator-(const Aws_DVector& vec) {
                this->x -= vec.x;
                this->y -= vec.y;
                this->z -= vec.z;
                this->w -= vec.w;

                return *this;
            }

            Aws_DVector operator*(const Aws_DVector& vec) {
                this->x *= vec.x;
                this->y *= vec.y;
                this->z *= vec.z;
                this->w *= vec.w;

                return *this;
            }

            Aws_DVector operator/(const Aws_DVector& vec) {
                this->x /= vec.x;
                this->y /= vec.y;
                this->z /= vec.z;
                this->w /= vec.w;

                return *this;
            }

            const Aws_DVector operator+(Aws_DVector& vec) {
                this->x += vec.x;
                this->y += vec.y;
                this->z += vec.z;
                this->w += vec.w;

                return *this;
            }

            const Aws_DVector operator-(Aws_DVector& vec) {
                this->x -= vec.x;
                this->y -= vec.y;
                this->z -= vec.z;
                this->w -= vec.w;

                return *this;
            }

            const Aws_DVector operator*(Aws_DVector& vec) {
                this->x *= vec.x;
                this->y *= vec.y;
                this->z *= vec.z;
                this->w *= vec.w;

                return *this;
            }

            const Aws_DVector operator/(Aws_DVector& vec) {
                this->x /= vec.x;
                this->y /= vec.y;
                this->z /= vec.z;
                this->w /= vec.w;

                return *this;
            }

            Aws_DVector operator+=(const Aws_DVector& vec) {
                this->x += vec.x;
                this->y += vec.y;
                this->z += vec.z;
                this->w += vec.w;

                return *this;
            }

            Aws_DVector operator-=(const Aws_DVector& vec) {
                this->x -= vec.x;
                this->y -= vec.y;
                this->z -= vec.z;
                this->w -= vec.w;

                return *this;
            }

            Aws_DVector operator*=(const Aws_DVector& vec) {
                this->x *= vec.x;
                this->y *= vec.y;
                this->z *= vec.z;
                this->w *= vec.w;

                return *this;
            }

            Aws_DVector operator/=(const Aws_DVector& vec) {
                this->x /= vec.x;
                this->y /= vec.y;
                this->z /= vec.z;
                this->w /= vec.w;

                return *this;
            }

            const Aws_DVector operator+=(Aws_DVector& vec) {
                this->x += vec.x;
                this->y += vec.y;
                this->z += vec.z;
                this->w += vec.w;

                return *this;
            }

            const Aws_DVector operator-=(Aws_DVector& vec) {
                this->x -= vec.x;
                this->y -= vec.y;
                this->z -= vec.z;
                this->w -= vec.w;

                return *this;
            }

            const Aws_DVector operator*=(Aws_DVector& vec) {
                this->x *= vec.x;
                this->y *= vec.y;
                this->z *= vec.z;
                this->w *= vec.w;

                return *this;
            }

            const Aws_DVector operator/=(Aws_DVector& vec) {
                this->x /= vec.x;
                this->y /= vec.y;
                this->z /= vec.z;
                this->w /= vec.w;

                return *this;
            }
        };

        struct Aws_Matrix 
        {
            float _matrix[4][4];

            Aws_Matrix() {
                this->_matrix[0][0] = 0.0f;
                this->_matrix[1][0] = 0.0f;
                this->_matrix[2][0] = 0.0f;
                this->_matrix[3][0] = 0.0f;
                this->_matrix[0][1] = 0.0f;
                this->_matrix[1][1] = 0.0f;
                this->_matrix[2][1] = 0.0f;
                this->_matrix[3][1] = 0.0f;
                this->_matrix[0][2] = 0.0f;
                this->_matrix[1][2] = 0.0f;
                this->_matrix[2][2] = 0.0f;
                this->_matrix[3][2] = 0.0f;
                this->_matrix[0][3] = 0.0f;
                this->_matrix[1][3] = 0.0f;
                this->_matrix[2][3] = 0.0f;
                this->_matrix[3][3] = 0.0f;
            }

            Aws_Matrix(float _value) {
                this->_matrix[0][0] = _value;
                this->_matrix[1][0] = _value;
                this->_matrix[2][0] = _value;
                this->_matrix[3][0] = _value;
                this->_matrix[0][1] = _value;
                this->_matrix[1][1] = _value;
                this->_matrix[2][1] = _value;
                this->_matrix[3][1] = _value;
                this->_matrix[0][2] = _value;
                this->_matrix[1][2] = _value;
                this->_matrix[2][2] = _value;
                this->_matrix[3][2] = _value;
                this->_matrix[0][3] = _value;
                this->_matrix[1][3] = _value;
                this->_matrix[2][3] = _value;
                this->_matrix[3][3] = _value;
            }

            Aws_Matrix(Aws_Vector _vector) {
                this->_matrix[0][0] = _vector.x;
                this->_matrix[1][0] = _vector.y;
                this->_matrix[2][0] = _vector.z;
                this->_matrix[3][0] = _vector.w;
                this->_matrix[0][1] = _vector.x;
                this->_matrix[1][1] = _vector.y;
                this->_matrix[2][1] = _vector.z;
                this->_matrix[3][1] = _vector.w;
                this->_matrix[0][2] = _vector.x;
                this->_matrix[1][2] = _vector.y;
                this->_matrix[2][2] = _vector.z;
                this->_matrix[3][2] = _vector.w;
                this->_matrix[0][3] = _vector.x;
                this->_matrix[1][3] = _vector.y;
                this->_matrix[2][3] = _vector.z;
                this->_matrix[3][3] = _vector.w;
            }

            Aws_Matrix(Aws_Vector _v1, Aws_Vector _v2) {
                this->_matrix[0][0] = _v1.x;
                this->_matrix[1][0] = _v1.y;
                this->_matrix[2][0] = _v1.z;
                this->_matrix[3][0] = _v1.w;
                this->_matrix[0][1] = _v2.x;
                this->_matrix[1][1] = _v2.y;
                this->_matrix[2][1] = _v2.z;
                this->_matrix[3][1] = _v2.w;
                this->_matrix[0][2] = 0.0f;
                this->_matrix[1][2] = 0.0f;
                this->_matrix[2][2] = 0.0f;
                this->_matrix[3][2] = 0.0f;
                this->_matrix[0][3] = 0.0f;
                this->_matrix[1][3] = 0.0f;
                this->_matrix[2][3] = 0.0f;
                this->_matrix[3][3] = 0.0f;
            }

            Aws_Matrix(Aws_Vector _v1, Aws_Vector _v2, Aws_Vector _v3) {
                this->_matrix[0][0] = _v1.x;
                this->_matrix[1][0] = _v1.y;
                this->_matrix[2][0] = _v1.z;
                this->_matrix[3][0] = _v1.w;
                this->_matrix[0][1] = _v2.x;
                this->_matrix[1][1] = _v2.y;
                this->_matrix[2][1] = _v2.z;
                this->_matrix[3][1] = _v2.w;
                this->_matrix[0][2] = _v3.x;
                this->_matrix[1][2] = _v3.y;
                this->_matrix[2][2] = _v3.z;
                this->_matrix[3][2] = _v3.w;
                this->_matrix[0][3] = 0.0f;
                this->_matrix[1][3] = 0.0f;
                this->_matrix[2][3] = 0.0f;
                this->_matrix[3][3] = 0.0f;
            }

            Aws_Matrix(Aws_Vector _v1, Aws_Vector _v2, Aws_Vector _v3, Aws_Vector _v4) {
                this->_matrix[0][0] = _v1.x;
                this->_matrix[1][0] = _v1.y;
                this->_matrix[2][0] = _v1.z;
                this->_matrix[3][0] = _v1.w;
                this->_matrix[0][1] = _v2.x;
                this->_matrix[1][1] = _v2.y;
                this->_matrix[2][1] = _v2.z;
                this->_matrix[3][1] = _v2.w;
                this->_matrix[0][2] = _v3.x;
                this->_matrix[1][2] = _v3.y;
                this->_matrix[2][2] = _v3.z;
                this->_matrix[3][2] = _v3.w;
                this->_matrix[0][3] = _v4.x;
                this->_matrix[1][3] = _v4.y;
                this->_matrix[2][3] = _v4.z;
                this->_matrix[3][3] = _v4.w;
            }

            Aws_Matrix(float _v1, float _v2, float _v3 = 0.0f, float _v4 = 0.0f, float _v5 = 0.0f, float _v6 = 0.0f, float _v7 = 0.0f, float _v8 = 0.0f, float _v9 = 0.0f, float _v10 = 0.0f, float _v11 = 0.0f, float _v12 = 0.0f, float _v13 = 0.0f, float _v14 = 0.0f, float _v15 = 0.0f, float _v16 = 0.0f) {
                this->_matrix[0][0] = _v1;
                this->_matrix[1][0] = _v2;
                this->_matrix[2][0] = _v3;
                this->_matrix[3][0] = _v4;
                this->_matrix[0][1] = _v5;
                this->_matrix[1][1] = _v6;
                this->_matrix[2][1] = _v7;
                this->_matrix[3][1] = _v8;
                this->_matrix[0][2] = _v9;
                this->_matrix[1][2] = _v10;
                this->_matrix[2][2] = _v11;
                this->_matrix[3][2] = _v12;
                this->_matrix[0][3] = _v13;
                this->_matrix[1][3] = _v14;
                this->_matrix[2][3] = _v15;
                this->_matrix[3][3] = _v16;
            }

            Aws_Matrix operator+(const Aws_Matrix& _mat) {
                this->_matrix[0][0] += _mat._matrix[0][0];
                this->_matrix[1][0] += _mat._matrix[1][0];
                this->_matrix[2][0] += _mat._matrix[2][0];
                this->_matrix[3][0] += _mat._matrix[3][0];
                this->_matrix[0][1] += _mat._matrix[0][1];
                this->_matrix[1][1] += _mat._matrix[1][1];
                this->_matrix[2][1] += _mat._matrix[2][1];
                this->_matrix[3][1] += _mat._matrix[3][1];
                this->_matrix[0][2] += _mat._matrix[0][2];
                this->_matrix[1][2] += _mat._matrix[1][2];
                this->_matrix[2][2] += _mat._matrix[2][2];
                this->_matrix[3][2] += _mat._matrix[3][2];
                this->_matrix[0][3] += _mat._matrix[0][3];
                this->_matrix[1][3] += _mat._matrix[1][3];
                this->_matrix[2][3] += _mat._matrix[2][3];
                this->_matrix[3][3] += _mat._matrix[3][3];
            }

            Aws_Matrix operator-(const Aws_Matrix& _mat) {
                this->_matrix[0][0] -= _mat._matrix[0][0];
                this->_matrix[1][0] -= _mat._matrix[1][0];
                this->_matrix[2][0] -= _mat._matrix[2][0];
                this->_matrix[3][0] -= _mat._matrix[3][0];
                this->_matrix[0][1] -= _mat._matrix[0][1];
                this->_matrix[1][1] -= _mat._matrix[1][1];
                this->_matrix[2][1] -= _mat._matrix[2][1];
                this->_matrix[3][1] -= _mat._matrix[3][1];
                this->_matrix[0][2] -= _mat._matrix[0][2];
                this->_matrix[1][2] -= _mat._matrix[1][2];
                this->_matrix[2][2] -= _mat._matrix[2][2];
                this->_matrix[3][2] -= _mat._matrix[3][2];
                this->_matrix[0][3] -= _mat._matrix[0][3];
                this->_matrix[1][3] -= _mat._matrix[1][3];
                this->_matrix[2][3] -= _mat._matrix[2][3];
                this->_matrix[3][3] -= _mat._matrix[3][3];
            }

            Aws_Matrix operator*(const Aws_Matrix& _mat) {
                this->_matrix[0][0] *= _mat._matrix[0][0];
                this->_matrix[1][0] *= _mat._matrix[0][1];
                this->_matrix[2][0] *= _mat._matrix[0][2];
                this->_matrix[3][0] *= _mat._matrix[0][3];
                this->_matrix[0][1] *= _mat._matrix[1][0];
                this->_matrix[1][1] *= _mat._matrix[1][1];
                this->_matrix[2][1] *= _mat._matrix[1][2];
                this->_matrix[3][1] *= _mat._matrix[1][3];
                this->_matrix[0][2] *= _mat._matrix[2][0];
                this->_matrix[1][2] *= _mat._matrix[2][1];
                this->_matrix[2][2] *= _mat._matrix[2][2];
                this->_matrix[3][2] *= _mat._matrix[2][3];
                this->_matrix[0][3] *= _mat._matrix[3][0];
                this->_matrix[1][3] *= _mat._matrix[3][1];
                this->_matrix[2][3] *= _mat._matrix[3][2];
                this->_matrix[3][3] *= _mat._matrix[3][3];
            }

            const Aws_Matrix operator+(Aws_Matrix& _mat) {
                this->_matrix[0][0] += _mat._matrix[0][0];
                this->_matrix[1][0] += _mat._matrix[1][0];
                this->_matrix[2][0] += _mat._matrix[2][0];
                this->_matrix[3][0] += _mat._matrix[3][0];
                this->_matrix[0][1] += _mat._matrix[0][1];
                this->_matrix[1][1] += _mat._matrix[1][1];
                this->_matrix[2][1] += _mat._matrix[2][1];
                this->_matrix[3][1] += _mat._matrix[3][1];
                this->_matrix[0][2] += _mat._matrix[0][2];
                this->_matrix[1][2] += _mat._matrix[1][2];
                this->_matrix[2][2] += _mat._matrix[2][2];
                this->_matrix[3][2] += _mat._matrix[3][2];
                this->_matrix[0][3] += _mat._matrix[0][3];
                this->_matrix[1][3] += _mat._matrix[1][3];
                this->_matrix[2][3] += _mat._matrix[2][3];
                this->_matrix[3][3] += _mat._matrix[3][3];
            }

            const Aws_Matrix operator-(Aws_Matrix& _mat) {
                this->_matrix[0][0] -= _mat._matrix[0][0];
                this->_matrix[1][0] -= _mat._matrix[1][0];
                this->_matrix[2][0] -= _mat._matrix[2][0];
                this->_matrix[3][0] -= _mat._matrix[3][0];
                this->_matrix[0][1] -= _mat._matrix[0][1];
                this->_matrix[1][1] -= _mat._matrix[1][1];
                this->_matrix[2][1] -= _mat._matrix[2][1];
                this->_matrix[3][1] -= _mat._matrix[3][1];
                this->_matrix[0][2] -= _mat._matrix[0][2];
                this->_matrix[1][2] -= _mat._matrix[1][2];
                this->_matrix[2][2] -= _mat._matrix[2][2];
                this->_matrix[3][2] -= _mat._matrix[3][2];
                this->_matrix[0][3] -= _mat._matrix[0][3];
                this->_matrix[1][3] -= _mat._matrix[1][3];
                this->_matrix[2][3] -= _mat._matrix[2][3];
                this->_matrix[3][3] -= _mat._matrix[3][3];
            }

            const Aws_Matrix operator*(Aws_Matrix& _mat) {
                this->_matrix[0][0] *= _mat._matrix[0][0];
                this->_matrix[1][0] *= _mat._matrix[0][1];
                this->_matrix[2][0] *= _mat._matrix[0][2];
                this->_matrix[3][0] *= _mat._matrix[0][3];
                this->_matrix[0][1] *= _mat._matrix[1][0];
                this->_matrix[1][1] *= _mat._matrix[1][1];
                this->_matrix[2][1] *= _mat._matrix[1][2];
                this->_matrix[3][1] *= _mat._matrix[1][3];
                this->_matrix[0][2] *= _mat._matrix[2][0];
                this->_matrix[1][2] *= _mat._matrix[2][1];
                this->_matrix[2][2] *= _mat._matrix[2][2];
                this->_matrix[3][2] *= _mat._matrix[2][3];
                this->_matrix[0][3] *= _mat._matrix[3][0];
                this->_matrix[1][3] *= _mat._matrix[3][1];
                this->_matrix[2][3] *= _mat._matrix[3][2];
                this->_matrix[3][3] *= _mat._matrix[3][3];
            }
        };

        template<typename T>
        size_t basicSearch(size_t _first, size_t _last, std::vector<T> arr, T value) {
            size_t index_beg = _first;
            size_t index_end = _last;
            size_t index_mid_end = (_last - _first) / 2;
            size_t index_mid_beg = (_last - _first) / 2;
            
            if (_last >= _first && _last < arr.size())
            {
                while (index_beg < index_mid_beg || index_end > index_mid_end)
                {
                    if(arr[index_beg] == value)
                    {
                        return index_beg;
                    }

                    if (arr[index_end] == value)
                    {
                        return index_end;
                    }

                    if (arr[index_mid_beg] == value)
                    {
                        return index_mid_beg;
                    }

                    if (arr[index_mid_end] == value)
                    {
                        return index_mid_end;
                    }

                    index_beg++;
                    index_end--;
                    index_mid_end++;
                    index_mid_beg--;
                }
            }

            return 1;
        }

        /**
         * @brief Ujemny search algorithm
         *
         * @tparam T typename
         * @tparam Arr data to search
         * @param _first first element
         * @param _last last element
         * @param arr data to research
         * @param _value value to be founded bt address
         * @return size_t
         */
        template<typename T, typename Arr>
        size_t Search(size_t _first, size_t _last, Arr *arr, T _value) {
            if (_last >= _first)
            {
                if (arr[_first] == _value)
                    return _first;

                if (arr[_last] == _value)
                    return _last;

                return Search(_first + 1, _last - 1, arr, _value);
            }

            return -1;
        }

        /**
         * @brief Ujemny search algorithm with vector
         *
         * @tparam T typename
         * @tparam Arr data to search
         * @param _first first element
         * @param _last last element
         * @param arr data to research
         * @param _value value to be founded bt address
         * @return size_t
         */
        template<typename T>
        size_t Search(size_t _first, size_t _last, std::vector<T> arr, T _value) {
            if (_last >= _first && _last < arr.size())
            {
                if (arr[_first] == _value)
                    return _first;

                if (arr[_last] == _value)
                    return _last;

                return Search(_first + 1, _last - 1, arr, _value);
            }

            return -1;
        }

        /**
         * @brief Linear search algorithm
         * 
         * @tparam T typename
         * @tparam Arr data to search
         * @param _first first element
         * @param _last last element
         * @param arr data to research
         * @param value value to be founded bt address
         * @return size_t 
         */
        template<typename T>
        size_t linSearch(size_t _first, size_t _last, T *arr, T value) {
            size_t pos;

            if (_first <= _last && value >= arr[_first] && value <= arr[_last]) {
                pos = _first + ((_last - _first) / (arr[_last] - arr[_first]) * (value - arr[_first]));

                if (arr[pos] == value)
                    return pos;

                if (arr[pos] < value)
                    return linSearch(pos + 1, _last, arr, value);

                if (arr[pos] > value)
                    return linSearch(_first, pos - 1, arr, value);
            }

            return -1;
        }

        /**
         * @brief Linear search algorithm
         *
         * @tparam T typename
         * @tparam Arr data to search
         * @param _first first element
         * @param _last last element
         * @param arr data to research
         * @param value value to be founded bt address
         * @return size_t
         */
        template<typename T>
        size_t linSearch(size_t _first, size_t _last, std::vector<T> arr, T value) {
            size_t pos;

            if (_first <= _last && value >= arr[_first] && value <= arr[_last]) {
                pos = _first + ((_last - _first) / (arr[_last] - arr[_first]) * (value - arr[_first]));

                if (arr[pos] == value)
                    return pos;

                if (arr[pos] < value)
                    return linSearch(pos + 1, _last, arr, value);

                if (arr[pos] > value)
                    return linSearch(_first, pos - 1, arr, value);
            }

            return -1;
        }

        /**
         * @brief Binary search algorithm
         * 
         * @tparam T typename
         * @tparam Arr data to search
         * @param _first first element
         * @param _last last element
         * @param arr data to research
         * @param value value to be founded bt address
         * @return size_t 
         */
        template<typename T, typename Arr>
        size_t binSearch(size_t _first, size_t _last, Arr arr[], T value) {
            if (_last >= _first) {
                int pos = _first + (_last - _first) / 2;

                if (arr[pos] == value)
                    return pos;

                if (arr[pos] > value)
                    return binSearch(_first, pos - 1, arr, value);

                return binSearch(pos + 1, _last, arr, value);
            }

            return -1;
        }

        /**
         * @brief Binary search algorithm
         *
         * @tparam T typename
         * @param _first first element
         * @param _last last element
         * @param arr data to research
         * @param value value to be founded bt address
         * @return size_t
         */
        template<typename T>
        size_t binSearch(size_t _first, size_t _last, std::vector<T> arr, T value) {
            if (_last >= _first) {
                int pos = _first + (_last - _first) / 2;

                if (arr[pos] == value)
                    return pos;

                if (arr[pos] > value)
                    return binSearch(_first, pos - 1, arr, value);

                return binSearch(pos + 1, _last, arr, value);
            }

            return -1;
        }

        /**
         * @brief Exponential search algorithm
         * 
         * @tparam T typename
         * @tparam Arr data to search
         * @param size size of data
         * @param arr data to research
         * @param value value to be founded bt address
         * @return size_t 
         */
        template<typename T>
        size_t expSearch(size_t size, T *arr, T value) {
            if (arr[0] == value)
                return arr[0];

            int i = 1;
            while (i < size && arr[i] <= value) {
                i = i * 2;
            }

            return binSearch(i / 2, fmin(i, size - 1), arr, value);
        }

        /**
         * @brief Ternary search algorithm
         * 
         * @tparam T typename
         * @tparam Arr data to search
         * @param _first first element
         * @param _last last element
         * @param arr data to research
         * @param value value to be founded bt address
         * @return size_t 
         */
        template<typename T>
        size_t ternSearch(size_t _first, size_t _last, T *arr, T value) {
            if (_last >= _first) {
                int pos1 = _first + (_last - 1) / 3;
                int pos2 = _last - (_last - 1) / 3;

                if (arr[pos1] == value)
                    return pos1;

                if (arr[pos2] == value)
                    return pos2;

                if (value < arr[pos1])
                    return ternSearch(_first, pos1 - 1, arr, value);
                else if (value > arr[pos2])
                    return ternSearch(pos2 + 1, _last, arr, value);
                else
                    return ternSearch(pos1 + 1, pos2 - 1, arr, value);
            }

            return -1;
        }

        /**
         * @brief Ternary search algorithm
         *
         * @tparam T typename
         * @tparam Arr data to search
         * @param _first first element
         * @param _last last element
         * @param arr data to research
         * @param value value to be founded bt address
         * @return size_t
         */
        template<typename T>
        size_t ternSearch(size_t _first, size_t _last, std::vector<T> arr, T value) {
            if (_last >= _first) {
                int pos1 = _first + (_last - 1) / 3;
                int pos2 = _last - (_last - 1) / 3;

                if (arr[pos1] == value)
                    return pos1;

                if (arr[pos2] == value)
                    return pos2;

                if (value < arr[pos1])
                    return ternSearch(_first, pos1 - 1, arr, value);
                else if (value > arr[pos2])
                    return ternSearch(pos2 + 1, _last, arr, value);
                else
                    return ternSearch(pos1 + 1, pos2 - 1, arr, value);
            }

            return -1;
        }

        /*
        * @brief Swap 2 values
        * 
        * @param _first
        * @param _second
        */
        template<class T>
        void swap(T* _first, T* _second) {
            T t = *_first;
            *_first = *_second;
            *_second = t;
        }

        /**
         * @brief Quick sort algorithm
         *
         * @tparam T typename
         * @tparam Arr data to sort
         * @param _begin first index
         * @param _end last index
         * @param arr data to sort
         * @return T* 
         */
        template<typename T>
        void quickSort(T *arr, size_t _begin, size_t _end) {
            if (_begin < _end) {
                T pivot = arr[_end];
                T i = (_begin - 1);

                for (int j = _begin; j <= _end; j++)
                {
                    if (arr[j] < pivot) {
                        i++;
                        swap(&arr[i], &arr[j]);
                    }
                }

                swap(&arr[i + 1], &arr[_end]);

                T part = i + 1;

                quickSort(arr, _begin, part - 1);
                quickSort(arr, part + 1, _end);
            }
        }
        
        /**
         * @brief inverse atan2 function
         * 
         * @tparam T 
         * @param radians angle in radians
         * @return T* return in order[x, y]
         */
        template<typename T>
        T* invatan2(T radians) {
            T _val[2];
            _val[0] = cos(radians);
            _val[1] = sin(radians);

            return _val;
        }

        /**
         * @brief Inverse sqrt
         * 
         * @tparam T 
         * @param _value 
         * @return T 
         */
        template<typename T>
        constexpr T invsqrt(T _value) noexcept {
            return (T)1 / sqrt(_value);
        }

        /**
         * @brief Quake Inverse sqrt
         * 
         * @tparam T 
         * @param _value 
         * @return T 
         */
        template<typename T>
        constexpr T fast_invsqrt(T _value) noexcept {
            static_assert(std::numeric_limits<T>::is_iec559); // (enable only on IEEE 754)

            T const y = std::bit_cast<T>( 0x5f3759df - (std::bit_cast<std::uint32_t>(_value) >> 1) );
            return y * (1.5f - (_value * 0.5f * y * y));
        }

        /**
         * @brief Get the Closest object
         * 
         * @tparam T 
         * @param val1 
         * @param val2 
         * @param target 
         * @return T 
         */
        template<typename T>
        T getClosest(T val1, T val2, T target)
        {
            if (target - val1 >= val2 - target)
                return val2;
            else
                return val1;
        }

        /**
         * @brief Gets and returns closest match of all array
         * 
         * @tparam T 
         * @param arr Array of values
         * @param target Targeted value
         * @return T 
         */
        template<typename T>
        T ClosestMatch(std::vector<T> arr, T target) {
            size_t index_beg = 0;
            size_t index_end = arr.size() - 1;

            T beg_closest = arr[0];
            T end_closest = arr[0];

            while (index_beg < index_end)
            {
                if (arr[index_beg] > target && beg_closest > arr[index_beg])
                {
                    beg_closest = arr[index_beg];
                }

                if (arr[index_beg] < target && beg_closest < arr[index_beg])
                {
                    beg_closest = arr[index_beg];
                }

                if (arr[index_end] > target && end_closest > arr[index_end])
                {
                    end_closest = arr[index_end];
                }

                if (arr[index_end] < target && end_closest < arr[index_end])
                {
                    end_closest = arr[index_end];
                }

                if (arr[index_beg] == target || arr[index_end] == target)
                {
                    return target;
                }

                index_beg++;
                index_end--;
            }

            if (beg_closest > end_closest && end_closest > target)
            {
                return end_closest;
            }
            else if (beg_closest < end_closest && end_closest < target)
            {
                return beg_closest;
            }

            return beg_closest;
        }

        /**
         * @brief Returns value only between range
         * 
         * @tparam T 
         * @param _min Min number
         * @param _max Max number
         * @param _value 
         * @return T 
         */
        template<typename T>
        T clamp(T _min, T _max, T _value) {
            if (_value > _max)
            {
                _value = _max;
                return _max;
            }
            else if (_value < _min)
            {
                _value = _min;
                return _min;
            }

            return _value;
        }

        /*
        * @brief Sphere to cartesian coordinates
        *
        * 
        */
        Aws_Vector SphereToCart(float _ZRad, float _XYRad, float _r = 1) {
            return Aws_Vector(_r * sin(_XYRad) * cos(_ZRad), _r* sin(_XYRad)* sin(_ZRad), _r* cos(_XYRad));
        }

        Aws_Vector CartToSphere(float _x, float _y, float _z) {
            return Aws_Vector(pow(tan(_y / _x), -1), pow(tan(sqrt(pow(_x, 2) + pow(_y, 2)) / _z), -1), sqrt(pow(_x, 2) + pow(_y, 2) + pow(_z, 2)));
        }

        /**
         * @brief Gives average of all vectors
         * 
         * @param _vecs 
         * @return Aws_Vector 
         */
        Aws_Vector avgVector(std::vector<Aws_Vector> _vecs) {
            Aws_Vector _avg_vec = {0.0f, 0.0f, 0.0f, 0.0f};

            for (uint32_t i = 0; i < _vecs.size(); i++) 
            {
                _avg_vec += _vecs[i];
            }

            _avg_vec /= Aws_Vector((float)_vecs.size(), (float)_vecs.size(), (float)_vecs.size(), (float)_vecs.size());

            return _avg_vec;
        }

        /*
        * @brief Dot product of 3D vector
        *
        *
        */
        float dot3D(Aws_Vector _first, Aws_Vector _second) {
            return _first.x * _first.y * _first.z + _second.x * _second.y * _second.z;
        }

        /*
        * @brief Dot product of 2D vector
        *
        *
        */
        float dot2D(Aws_Vector _first, Aws_Vector _second) {
            return _first.x * _first.y + _second.x * _second.y;
        }

        /*float getLambda3D(Aws_Vector _first_nor, Aws_Vector _second_nor, Aws_Vector _third_nor) {
            return (-dot3D(_first_nor) - dot3D(_second_nor)) / dot3D(_third_nor);
        }

        float getLambda2D(Aws_Vector _first_nor, Aws_Vector _second_nor, Aws_Vector _third_nor) {
            return (-dot2D(_first_nor) - dot2D(_second_nor)) / dot2D(_third_nor);
        }*/

        Aws_Vector to_vec(float _value) {
            return Aws_Vector(_value, _value, _value, _value);
        }

        Aws_DVector to_dvec(double _value) {
            return Aws_DVector(_value, _value, _value, _value);
        }

        /**
         * @brief Convert degrees to radians
         * 
         * @tparam T 
         * @param degrees 
         * @return T 
         */
        template<typename T>
        T to_radians(T degrees) {
            return degrees * static_cast<T>(0.01745329251994329576923690768489);
        }

        /**
         * @brief Convert radians to degrees
         * 
         * @tparam T 
         * @param radians 
         * @return T 
         */
        template<typename T>
        T to_degrees(T radians) {
            return radians * static_cast<T>(57.295779513082320876798154814105);
        }

        /**
         * @brief Gives max value of 2 parameters
         * 
         * @tparam T 
         * @param _v1 value 1
         * @param _v2 value 2
         * @return T 
         */
        template<typename T>
        T Max(T _v1, T _v2) {
            return _v1 > _v2 ? _v1 : _v2;
        }

        /**
         * @brief Gives max value of 3 parameters
         * 
         * @tparam T 
         * @param _v1 value 1
         * @param _v2 value 2
         * @param _v3 value 3
         * @return T 
         */
        template<typename T>
        T Max3(T _v1, T _v2, T _v3) {
            return _v1 > _v2 ? (_v1 > _v3 ? _v1 : _v3) : (_v2 > _v3 ? _v2 : _v3);
        }

        /**
         * @brief Gives max value of vector
         * 
         * @param _vec vector
         * @return float
         */
        float MaxVector3(Aws_Vector _vec) {
            return _vec.x > _vec.y ? (_vec.x > _vec.z ? _vec.x : _vec.z) : (_vec.y > _vec.z ? _vec.y : _vec.z);
        }

        /**
         * @brief Gives min value of 2 parameters
         * 
         * @tparam T 
         * @param _v1 value 1
         * @param _v2 value 2
         * @return T 
         */
        template<typename T>
        T Min(T _v1, T _v2) {
            return _v1 < _v2 ? _v1 : _v2;
        }

        /**
         * @brief Gives min value of 3 parameters
         * 
         * @tparam T 
         * @param _v1 value 1
         * @param _v2 value 2
         * @param _v3 value 3
         * @return T 
         */
        template<typename T>
        T Min3(T _v1, T _v2, T _v3) {
            return _v1 < _v2 ? (_v1 < _v3 ? _v1 : _v3) : (_v2 < _v3 ? _v2 : _v3);
        }

        /**
         * @brief Gives min value of vector
         * 
         * @param _vec value 1
         * @return float
         */
        float MinVector3(Aws_Vector _vec) {
            return _vec.x < _vec.y ? (_vec.x < _vec.z ? _vec.x : _vec.z) : (_vec.y < _vec.z ? _vec.y : _vec.z);
        }

        /**
         * @brief Mormalize vector parameters to 1 and smaller
         * 
         * @param vector Vector
         * @return Aws_Vector 
         */
        Aws_Vector NormalizeVector(Aws_Vector vector) {
            return Aws_Vector(vector.x, vector.y, vector.z, 1.0f) / to_vec(MaxVector3(vector));
        }

        /**
         * @brief Normalize vector parameters to 1 and smaller
         * 
         * @param vector Double type vector
         * @return Aws_DVector 
         */
        Aws_DVector NormalizeDVector(Aws_DVector vector) {
            return Aws_DVector(vector.x, vector.y, vector.z, 1.0) / to_dvec(vector.x > vector.y ? (vector.x > vector.z ? vector.x : vector.z) : (vector.y > vector.z ? vector.y : vector.z));
        }

        glm::mat3 AngleToMatrix3(Aws_Vector _angle) {
            glm::mat3 r_x = glm::mat3(
                1.0f, 0.0f, 0.0f,
                0.0f, cos(_angle.x), -sin(_angle.x),
                0.0f, sin(_angle.x), cos(_angle.x)
                );

            glm::mat3 r_y = glm::mat3(
                cos(_angle.y), 0.0f, sin(_angle.y),
                0.0f, 1.0f, 0.0f,
                -sin(_angle.y), 0.0f, cos(_angle.y)
                );

            glm::mat3 r_z = glm::mat3(
                cos(_angle.z), -sin(_angle.z), 0.0f,
                sin(_angle.z), cos(_angle.z), 0.0f,
                0.0f, 0.0f, 1.0f
                );

            return r_z * r_y * r_x;
        }

        Aws_Vector Matrix3ToAngle(glm::mat3 _rotation_matrix) {
            float sy = sqrt(_rotation_matrix[0][0] * _rotation_matrix[0][0] + _rotation_matrix[1][0] * _rotation_matrix[1][0]);

            bool singular = sy < 1e-6;

            Aws_Vector angle;

            if(!singular)
            {
                angle.x = atan2(_rotation_matrix[2][1], _rotation_matrix[2][2]);
                angle.y = atan2(-_rotation_matrix[2][0], sy);
                angle.z = atan2(_rotation_matrix[1][0], _rotation_matrix[0][0]);
            }
            else
            {
                angle.x = atan2(_rotation_matrix[1][2], _rotation_matrix[1][1]);
                angle.y = atan2(-_rotation_matrix[2][0], sy);
                angle.z = 0.0f;
            }

            return angle;
        }

        /**
         * @brief Calculates vector from 3x3 matrix
         * 
         * @param _rotation_matrix Matrix of calculated rotations (consider to use AngleToMatrix function)
         * @param _rotation Vector with rotations(points of mesh that matrix data would be multiplied)
         * @return Aws_Vector 
         */
        Aws_Vector Matrix3ToVector(glm::mat3 _rotation_matrix, Aws_Vector rotation = {1.0f, 1.0f, 1.0f}) {
            Aws_Vector _rotation = NormalizeVector(rotation);

            return {
                _rotation_matrix[0][0] * _rotation.x + _rotation_matrix[0][1] * _rotation.y + _rotation_matrix[0][2] * _rotation.z, 
                _rotation_matrix[1][0] * _rotation.x + _rotation_matrix[1][1] * _rotation.y + _rotation_matrix[1][2] * _rotation.z, 
                _rotation_matrix[2][0] * _rotation.x + _rotation_matrix[2][1] * _rotation.y + _rotation_matrix[2][2] * _rotation.z, 
                };
        }

        /**
         * @brief Calculates vector from 4x4 matrix
         * 
         * @param _rotation_matrix Matrix of calculated rotations (consider to use AngleToMatrix function)
         * @param _rotation Vector with rotations(points of mesh that matrix data would be multiplied)
         * @return Aws_Vector 
         */
        Aws_Vector Matrix4ToVector(glm::mat4 _rotation_matrix, Aws_Vector rotation = {1.0f, 1.0f, 1.0f}) {
            Aws_Vector _rotation = NormalizeVector(rotation);

            return {
                _rotation_matrix[0][0] * _rotation.x + _rotation_matrix[0][1] * _rotation.y + _rotation_matrix[0][2] * _rotation.z, 
                _rotation_matrix[1][0] * _rotation.x + _rotation_matrix[1][1] * _rotation.y + _rotation_matrix[1][2] * _rotation.z, 
                _rotation_matrix[2][0] * _rotation.x + _rotation_matrix[2][1] * _rotation.y + _rotation_matrix[2][2] * _rotation.z, 
                };
        }

        /**
         * @brief Somehow calculates good rotation, i just tried it and it worked
         * 
         * @param _rotation_matrix Matrix of calculated rotations (consider to use AngleToMatrix function)
         * @param _rotation Vector with rotations(points of mesh that matrix data would be multiplied)
         * @return Aws_Vector 
         */
        Aws_Vector NormalizedMatrix3ToValues(glm::mat3 _rotation_matrix, Aws_Vector _rotation = {1.0f, 1.0f, 1.0f}) {
            Aws_Vector _result_rotation = {
                _rotation_matrix[0][0] * _rotation.x + _rotation_matrix[0][1] * _rotation.y + _rotation_matrix[0][2] * _rotation.z, 
                _rotation_matrix[1][0] * _rotation.x + _rotation_matrix[1][1] * _rotation.y + _rotation_matrix[1][2] * _rotation.z, 
                _rotation_matrix[2][0] * _rotation.x + _rotation_matrix[2][1] * _rotation.y + _rotation_matrix[2][2] * _rotation.z, 
                };

            Aws_Vector old = _result_rotation;

            _result_rotation.x = old.x / MaxVector3(_result_rotation);
            _result_rotation.y = old.y / MaxVector3(_result_rotation);
            _result_rotation.z = old.z / MaxVector3(_result_rotation);

            if (_result_rotation.x > 1.0f || _result_rotation.x < -1.0f || _result_rotation.y > 1.0f || _result_rotation.y < -1.0f || _result_rotation.z > 1.0f || _result_rotation.z < -1.0f)
                return _result_rotation;
            else
            {
                _result_rotation.x = old.x / MaxVector3(_result_rotation) == 0.0f ? 0.0001f : MaxVector3(_result_rotation);
                _result_rotation.y = old.y / MaxVector3(_result_rotation) == 0.0f ? 0.0001f : MaxVector3(_result_rotation);
                _result_rotation.z = old.z / MaxVector3(_result_rotation) == 0.0f ? 0.0001f : MaxVector3(_result_rotation);

                fprintf(__debug_file, "X: %.2f,\t Y: %.2f,\t Z: %.2f\n", _result_rotation.x, _result_rotation.y, _result_rotation.z);

                return _result_rotation;
            }

        }

        template<typename T>
        Aws_Vector RodriguesRotation(T angle, glm::mat3 _rotation_matrix, Aws_Vector axis, Aws_Vector points) {
            Aws_Vector v = Matrix3ToVector(_rotation_matrix);

            Aws_Vector _result =  v * to_vec(cos(angle)) + ( axis * v ) + to_vec(sin(angle)) + axis * ( axis * v ) * to_vec(1.0f - cos(angle));

            return _result * points;
        }

        typedef Aws_Vector Vector;
        typedef Aws_DVector DVector;
        typedef Aws_Matrix Matrix;
    }
}