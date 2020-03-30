#include "helpers.hpp"

std::string HELPERS::resolvePath(std::string path) {
	wxFileName fullPath("../" + path, wxPATH_NATIVE);
	fullPath.MakeAbsolute();
	std::string res = fullPath.GetFullPath(wxPATH_NATIVE).ToStdString();
	return res;
};

std::vector<std::string> HELPERS::splitString(const std::string s, char delim) {
	std::vector<std::string> result;
	std::stringstream ss(s);
	std::string item;

	while(std::getline(ss, item, delim)) {
		result.push_back(item);
	}

	return result;
}

std::string HELPERS::joinString(std::vector<std::string> vec, std::string delimiter) {
	if(vec.size() != 0) {
		// https://stackoverflow.com/a/40052831
		// clang-format off
		return std::accumulate(std::next(vec.begin()), vec.end(),
			vec[0],
		[&delimiter](std::string& a, std::string& b) {
			return a + delimiter + b;
		});
		// clang-format on
	} else {
		return "";
	}
}

float HELPERS::normalizeRadian(float angle) {
	float a = std::fmod(angle, 2 * M_PI);
	return a >= 0 ? a : (a + 2 * M_PI);
}

rapidjson::Document HELPERS::getSettingsFile(std::string filename) {
	rapidjson::Document json;
	std::ifstream file(filename);
	std::string content((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
	// Allow comments in JSON
	json.Parse<rapidjson::kParseCommentsFlag>(content.c_str());
	return json;
}

wxBitmapButton* HELPERS::getBitmapButton(wxWindow* parentFrame, rapidjson::Document* settings, const char* name) {
	wxImage resizedImage(HELPERS::resolvePath((*settings)["ui"][name].GetString()));
	resizedImage.Rescale((*settings)["ui"]["buttonWidth"].GetInt(), (*settings)["ui"]["buttonHeight"].GetInt());
	return new wxBitmapButton(parentFrame, wxID_ANY, *(new wxBitmap(resizedImage)));
}

// https://stackoverflow.com/a/478960/9329945
// Executes command and gets output
std::string HELPERS::exec(const char* cmd) {
	std::array<char, 128> buffer;
	std::string result;
	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
	if(!pipe) {
		throw std::runtime_error("popen() failed!");
	}
	while(fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
		result += buffer.data();
	}
	return result;
}