#using <System.dll>

using namespace System;

namespace NSass
{
	public ref class SassOptions
	{
		public:
			property int OutputStyle;
			property bool SourceComments;
			property String^ SourceMapFile;
			property bool OmitSourceMapUrl;
			property bool SourceMapEmbed;
			property bool SourceMapContents;
			property String^ SourceMapRoot;
			property bool IsIndentedSyntaxSrc;
			property String^ IncludePaths;
			property String^ PluginPaths;
			property String^ Indent;
			property String^ Linefeed;
			property int Precision;
	};

	public ref class SassContext
	{
		public:
			property String^ SourceString;
			property String^ OutputString;
			property SassOptions^ Options;
			property bool ErrorStatus;
			property String^ ErrorMessage;
	};

	public ref class SassFileContext
	{
		public:
			property String^ InputPath;
			property String^ OutputString;
			property SassOptions^ Options;
			property bool ErrorStatus;
			property String^ ErrorMessage;
	};

	public ref class SassFolderContext
	{
		public:
			property String^ SearchPath;
			property String^ OutputPath;
			property SassOptions^ Options;
			property bool ErrorStatus;
			property String^ ErrorMessage;
	};
}