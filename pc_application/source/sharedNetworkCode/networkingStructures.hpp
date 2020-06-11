#pragma once

#include "include/zpp.hpp"
#include <cstdint>
#include <memory>

#include "buttonData.hpp"

// clang-format off
#define DEFINE_STRUCT(Flag, body, ...) \
	struct Struct_##Flag : public zpp::serializer::polymorphic { \
		DataFlag flag = DataFlag::Flag; \
		body \
		friend zpp::serializer::access; \
		template <typename Archive, typename Self> static void serialize(Archive& archive, Self& self) { \
			archive(__VA_ARGS__); \
		} \
	};
// clang-format on

enum DataFlag : uint8_t {
	SendFrameData,
	RecieveGameFramebuffer,
	RecieveGameInfo,
	SendFlag,
	SendAutoRun,
	SendLogging,
	SendTrackMemoryRegion,
	SendSetNumControllers,
	RecieveMemoryRegion,
	RecieveLogging,
	RecieveFlag,
	RecieveApplicationConnected,
	RecieveGameMemoryInfo,
	RecieveAutoRunControllerData,
	NUM_OF_FLAGS,
};

enum RecieveInfo : uint8_t {
	RUN_FRAME_DONE,
	FRAMEBUFFER_DONE,
	APPLICATION_DISCONNECTED,
	CONTROLLERS_CONNECTED,
	UNEXPECTED_CONTROLLER_SIZE,
};

enum SendInfo : uint8_t {
	GET_FRAMEBUFFER,
	GET_GAME_INFO,
	START_TAS_MODE,
	END_TAS_MODE,
	PAUSE_DEBUG,
	UNPAUSE_DEBUG,
	// These methods aren't debug because they are called by savestateHandler
	PAUSE,
	UNPAUSE,
	RUN_BLANK_FRAME,
};

// clang-format off
namespace Protocol {
	// Run a single frame and return when done
	DEFINE_STRUCT(SendFrameData,
		ControllerData controllerData;
		// This is the frame of this frame, the framebuffer
		// sent back will be one more than this frame
		uint32_t frame;
		uint16_t savestateHookNum;
		uint8_t playerIndex;
		uint8_t incrementFrame;
	, self.controllerData, self.frame, self.playerIndex, self.incrementFrame, self.savestateHookNum)

	// Recieve all of the game's framebuffer
	DEFINE_STRUCT(RecieveGameFramebuffer,
		std::vector<uint8_t> buf;
		uint8_t fromFrameAdvance;
		uint32_t frame;
		uint16_t savestateHookNum;
		uint8_t playerIndex;
	, self.buf, self.fromFrameAdvance, self.frame, self.savestateHookNum, self.playerIndex)

	// Recieve a ton of game and user info
	DEFINE_STRUCT(RecieveGameInfo,
		std::string applicationName;
		uint64_t applicationProgramId;
		uint64_t applicationProcessId;
		//std::string userNickname;
		std::vector<GameMemoryInfo> memoryInfo;
	, self.applicationName, self.applicationProgramId, self.applicationProcessId, self.memoryInfo)

	// Send start, with mostly everything as an enum value
	DEFINE_STRUCT(SendFlag,
		SendInfo actFlag;
	, self.actFlag)

	DEFINE_STRUCT(SendAutoRun,
		uint8_t fps;
		// This is a bool
		uint8_t start;
		uint32_t frameStart;
		uint16_t savestateHookNum;
		uint8_t playerIndex;
	, self.fps, self.start, self.frameStart, self.savestateHookNum, self.playerIndex)

	DEFINE_STRUCT(SendLogging,
		std::string log;
	, self.log)

	DEFINE_STRUCT(SendTrackMemoryRegion,
		uint64_t startByte;
		uint64_t size;
	, self.startByte, self.size)

	DEFINE_STRUCT(SendSetNumControllers,
		uint8_t size;
	, self.size)

	DEFINE_STRUCT(RecieveMemoryRegion,
		uint64_t startByte;
		uint64_t size;
		std::vector<uint8_t> memory;
	, self.startByte, self.size, self.memory)

	DEFINE_STRUCT(RecieveLogging,
		std::string log;
	, self.log)

	// Recieve done, with mostly everything as an enum value
	DEFINE_STRUCT(RecieveFlag,
		RecieveInfo actFlag;
	, self.actFlag)

	DEFINE_STRUCT(RecieveApplicationConnected,
		std::string applicationName;
		uint64_t applicationProgramId;
		uint64_t applicationProcessId;
	, self.applicationName, self.applicationProgramId, self.applicationProcessId)

	DEFINE_STRUCT(RecieveAutoRunControllerData,
		std::shared_ptr<ControllerData> controllerData;
	, self.controllerData)
};
// clang-format on