// 今のところ使い道はないがカメラや補間のために枠だけ作っている

#pragma once

struct QUATERNION_D
{
	double	m_x,	// 回転軸のベクトルx成分
		m_y,		// 回転軸のベクトルy成分
		m_z,		// 回転軸のベクトルz成分
		m_w;		// 回転角
};

class Quaternion
{
private:
	QUATERNION_D m_quat;

public:
	Quaternion(QUATERNION_D quat);
	virtual ~Quaternion();

public:
	
};