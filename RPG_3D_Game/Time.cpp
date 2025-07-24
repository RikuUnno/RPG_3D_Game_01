#include "TIme.h"
#include "DxLib.h"

Time::Time()
{
	m_currentFrame = 0;
	m_previousFrame = 0;
	m_deltaTime = 0;
}

Time::~Time()
{}

void Time::Update()
{
	// deltaTimeの処理
	m_previousFrame = m_currentFrame; // 前フレームの時間の保存
	m_currentFrame = GetNowCount();	// 現在のフレームの経過時間
	m_deltaTime = (m_currentFrame - m_previousFrame) / 1000.0; // ミリ秒→秒


}

double Time::DeltaTime()
{
	return m_deltaTime;
}