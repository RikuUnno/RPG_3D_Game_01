#pragma once
#include <stdint.h>

// ビットマスク用のLayer
enum class Layer : uint32_t {
	None	= 0,
	Player	= 1 << 0,
	Enemy	= 1 << 1,
	Wall	= 1 << 2
};

// ビット演算オーバーロード
inline Layer operator|(Layer a, Layer b) {
	return static_cast<Layer>(
		static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}

inline Layer operator&(Layer a, Layer b) {
	return static_cast<Layer>(
		static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
}

// Layerが0かどうか判定する関数
inline bool Any(Layer l) {
	return static_cast<uint32_t>(l) != 0;
}