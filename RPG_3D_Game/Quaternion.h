// ���̂Ƃ���g�����͂Ȃ����J�������Ԃ̂��߂ɘg��������Ă���

#pragma once

struct QUATERNION_D
{
	double	m_x,	// ��]���̃x�N�g��x����
		m_y,		// ��]���̃x�N�g��y����
		m_z,		// ��]���̃x�N�g��z����
		m_w;		// ��]�p
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