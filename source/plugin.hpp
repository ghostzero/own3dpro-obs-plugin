#pragma once
#include <cinttypes>
#include <filesystem>
#include <string>
#include <vector>
#include "version.hpp"

#include <obs-module.h>
#include <util/platform.h>
#undef strtoll

#ifdef WIN32
#define OWN3D_USER_AGENT "Own3d.tv OBS Plugin/" OWN3DTV_VERSION_STRING " (Windows)"
#elif APPLE
#define OWN3D_USER_AGENT "Own3d.tv OBS Plugin/" OWN3DTV_VERSION_STRING " (MacOS)"
#else
#define OWN3D_USER_AGENT "Own3d.tv OBS Plugin/" OWN3DTV_VERSION_STRING " (Unix)"
#endif

// Common Global defines
/// Log Functionality
#define DLOG_PREFIX "[Own3d.TV]"
#define DLOG_(level, ...) blog(level, DLOG_PREFIX " " __VA_ARGS__)
#define DLOG_ERROR(...) DLOG_(LOG_ERROR, __VA_ARGS__)
#define DLOG_WARNING(...) DLOG_(LOG_WARNING, __VA_ARGS__)
#define DLOG_INFO(...) DLOG_(LOG_INFO, __VA_ARGS__)
#define DLOG_DEBUG(...) DLOG_(LOG_DEBUG, __VA_ARGS__)
/// Currrent function name (as const char*)
#ifdef _MSC_VER
// Microsoft Visual Studio
#define __FUNCTION_SIG__ __FUNCSIG__
#define __FUNCTION_NAME__ __func__
#elif defined(__GNUC__) || defined(__MINGW32__)
// GCC and MinGW
#define __FUNCTION_SIG__ __PRETTY_FUNCTION__
#define __FUNCTION_NAME__ __func__
#else
// Any other compiler
#define __FUNCTION_SIG__ __func__
#define __FUNCTION_NAME__ __func__
#endif

namespace own3d {
	inline void source_deleter(obs_source_t* v)
	{
		obs_source_release(v);
	}

	inline void sceneitem_deleter(obs_sceneitem_t* v)
	{
		obs_sceneitem_remove(v);
	}

	inline void data_deleter(obs_data_t* v)
	{
		obs_data_release(v);
	}

	inline void data_item_deleter(obs_data_item_t* v)
	{
		obs_data_item_release(&v);
	}

	inline void data_array_deleter(obs_data_array_t* v)
	{
		obs_data_array_release(v);
	}

	class configuration {
		std::shared_ptr<obs_data_t> _data;
		std::filesystem::path       _data_path;
		std::filesystem::path       _data_path_bk;

		public:
		~configuration();

		configuration();

		std::shared_ptr<obs_data_t> get();

		void save();

		// Singleton
		private:
		static std::shared_ptr<own3d::configuration> _instance;

		public:
		static void initialize();
		static void finalize();

		static std::shared_ptr<own3d::configuration> instance();
	};

	std::string get_api_endpoint(std::string_view const args = "");

	bool testing_enabled();

	std::string_view testing_archive_name();

	std::string_view testing_archive_path();

	std::string_view get_unique_identifier();

	void reset_unique_identifier();
} // namespace own3d

#define D_TRANSLATE(x) obs_module_text(x)
