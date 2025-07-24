#pragma once
#include <stdint.h>

// �r�b�g�}�X�N�p��Layer
enum class Layer : uint32_t {
	None	= 0,
	Player	= 1 << 0,
	Enemy	= 1 << 1,
	Wall	= 1 << 2
};

// �r�b�g���Z�I�[�o�[���[�h
inline Layer operator|(Layer a, Layer b) {
	return static_cast<Layer>(
		static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}

inline Layer operator&(Layer a, Layer b) {
	return static_cast<Layer>(
		static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
}

// Layer��0���ǂ������肷��֐�
inline bool Any(Layer l) {
	return static_cast<uint32_t>(l) != 0;
}