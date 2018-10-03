#include "stdinc.h"
#include "byte_pattern.h"

namespace Font {

	/*-----------------------------------------------*/

	errno_t heepZero_hook() {
		byte_pattern::temp_instance().find_pattern("59 85 C0 74 15 56 6A 00");
		if (byte_pattern::temp_instance().has_size(1,"v1.25.X")) {
			// push 0
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0x7), 0x08, true);
		}
		else {
			return 1;
		}

		return 0;
	}

	/*-----------------------------------------------*/

	errno_t bufferClear_hook() {
		
		/* ランチャー */
		byte_pattern::temp_instance().find_pattern("68 20 28 00 00 8B 45");
		if (byte_pattern::temp_instance().has_size(1,"v1.25.X")) {
			// push 2820h
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(3), 0x04, true);
		}
		else {
			return 1;
		}

		/* ランチャー */
		byte_pattern::temp_instance().find_pattern("68 20 28 00 00 56 E8");
		if (byte_pattern::temp_instance().has_size(1, "v1.25.X")) {
			// push 2820h
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(3), 0x04, true);
		}
		else {
			return 1;
		}

		/* 本体 */
		byte_pattern::temp_instance().find_pattern("68 50 28 00 00 8B 45");
		if (byte_pattern::temp_instance().has_size(1, "v1.25.X")) {
			// push 2850h
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(3), 0x04, true);
		}
		else {
			return 1;
		}

		/* 本体 */
		byte_pattern::temp_instance().find_pattern("68 50 28 00 00 56 E8");
		if (byte_pattern::temp_instance().has_size(1, "v1.25.X")) {
			// push 2850h
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(3), 0x04, true);
		}
		else {
			return 1;
		}

		return 0;
	}

	/*-----------------------------------------------*/

	errno_t fontSize_hook() {
		byte_pattern::temp_instance().find_pattern("81 FE 00 00 00 01");
		if (byte_pattern::temp_instance().has_size(1, "v1.25.X")) {
			// cmp esi, 10000000h
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0x5), 0x04, true);
		}
		else {
			return 1;
		}

		return 0;
	}

	/*-----------------------------------------------*/

	errno_t bufferExp_hook() {

		/* ランチャー */
		byte_pattern::temp_instance().find_pattern("68 20 28 00 00 E8 ? ? ? ? 83");
		if (byte_pattern::temp_instance().has_size(1, "v1.25.X")) {
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(3), 0x04, true);
		}
		else {
			return 1;
		}

		/* 本体 */
		byte_pattern::temp_instance().find_pattern("68 50 28 00 00 E8 ? ? ? ? 83");
		if (byte_pattern::temp_instance().has_size(1, "v1.25.X")) {
			injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(3), 0x04, true);
		}
		else {
			return 1;
		}

		return 0;
	}

	/*-----------------------------------------------*/

	errno_t init() {
		errno_t result = 0;

		/* ヒープゼロフラグの修正 */
		result |= heepZero_hook();
		/* フォントバッファクリア */
		result |= bufferClear_hook();
		/* フォントバッファ拡張 */
		result |= bufferExp_hook();
		/* フォントサイズの拡張 */
		result |= fontSize_hook();

		return result;
	}
}