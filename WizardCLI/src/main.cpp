#include <iostream>
#include <string>
#include <cstring>

#include <BuildManager.h>
#include <Reporter.hpp>

void printUsage() {
	std::cout << "Usage: wizard <GTA_SA_DIR> [--samp] [--custom] [--output <file>]" << std::endl << std::endl;
	std::cout << "Example: ./wizard /sdcard/.../files/ --output /storage/emulated/0/ColAndreas.cadb" << std::endl;
	std::cout << "  --samp	Include SA-MP objects" << std::endl;
	std::cout << "  --custom  Include custom.img objects" << std::endl;
}

int main(int argc, char* argv[]) {
	if(argc < 2) {
		printUsage();
		return 1;
	}

	std::string gamePath;
	std::string outputPath = "ColAndreas.cadb";
	bool samp = false, custom = false;

	for(int i = 1; i < argc; ++i) {
		if(strcmp(argv[i], "--samp") == 0) samp = true;
		else if(strcmp(argv[i], "--custom") == 0) custom = true;
		else if(strcmp(argv[i], "--output") == 0 && i+1 < argc) outputPath = argv[++i];
		else if(argv[i][0] != '-') gamePath = argv[i];
	}

	#ifdef WIN32
		std::replace(gamePath.begin(), gamePath.end(), '/', '\\');
		std::replace(outputPath.begin(), outputPath.end(), '/', '\\');
	#endif

	if(gamePath.empty()) {
		std::cerr << "Error: No GTA:SA directory provided." << std::endl;
		printUsage();
		return 1;
	}

	// Remove trailing slash if present
	if(gamePath.back() == '/' || gamePath.back() == '\\')
		gamePath.pop_back();

	ConsoleReporter reporter;
	reporter.addFormattedMessage("ColAndreas Wizard CLI");
	reporter.addFormattedMessage("Game directory: %s", gamePath.c_str());
	reporter.addFormattedMessage("Output file: %s", outputPath.c_str());
	reporter.addFormattedMessage("SAMP objects: %s, Custom objects: %s", samp ? "yes" : "no", custom ? "yes" : "no");

	BuildManager build(&reporter, gamePath, outputPath, samp, custom);

	reporter.reportProgress(1, "Processing: Image files (.img)");
	build.ExtractImageFiles();
	reporter.reportProgress(15, "Done.");

	reporter.reportProgress(1, "Processing: Collision files (.col)");
	build.ExtractCollisionFiles();
	reporter.reportProgress(15, "Done.");

	reporter.reportProgress(1, "Processing: Item placement files (.ipl)");
	build.ExtractItemPlacementFiles();
	reporter.reportProgress(15, "Done.");

	reporter.reportProgress(1, "Processing: Item definition files (.ide)");
	build.ExtractItemDefinitionFiles();
	reporter.reportProgress(15, "Done.");

	reporter.reportProgress(1, "Preparing database structures...");
	build.PrepareDatabaseStructures();
	reporter.reportProgress(15, "Done.");

	reporter.reportProgress(1, "Writing the database file...");
	if(build.WriteBinaryFile(outputPath.c_str())) {
		reporter.reportProgress(15, "Done.");
		reporter.setProgress(100);
		reporter.addMessage("All done!");
	} else {
		reporter.addMessage("Error writing file.");
		return 1;
	}

	return 0;
}