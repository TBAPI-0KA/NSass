#include <exception>
#include "AssemblyInfo.hpp"
#include "sass_interface.h"
#include "StringToANSI.hpp"
#include "SassInterface.hpp"

using namespace std;

namespace NSass
{
	int SassInterface::Compile(SassContext^ sassContext)
	{
		sass_context* ctx = sass_new_context();
		try
		{
			// Copy fields from managed structure to unmanaged
			ctx -> source_string = MarshalConstString(sassContext -> SourceString);
			//ctx -> included_files = MarshalStringArray(gcnew array<String^>(0));
			if (sassContext -> Options)
			{
				ctx -> options.output_style = sassContext -> Options -> OutputStyle;
				ctx -> options.source_comments = sassContext -> Options -> SourceComments;
				ctx -> options.source_map_file = MarshalString(sassContext -> Options -> SourceMapFile);
				ctx -> options.omit_source_map_url = sassContext -> Options -> OmitSourceMapUrl;
				ctx -> options.source_map_embed = sassContext -> Options -> SourceMapEmbed;
				ctx -> options.source_map_contents = sassContext -> Options -> SourceMapContents;
				ctx -> options.source_map_root = MarshalString(sassContext -> Options -> SourceMapRoot);
				ctx -> options.is_indented_syntax_src = sassContext -> Options -> IsIndentedSyntaxSrc;
				ctx -> options.include_paths = MarshalString(sassContext -> Options -> IncludePaths);
				ctx -> options.plugin_paths = MarshalString(sassContext -> Options -> PluginPaths);
				ctx -> options.indent = MarshalString(sassContext -> Options -> Indent);
				ctx -> options.linefeed = MarshalString(sassContext -> Options -> Linefeed);
				ctx -> options.precision = sassContext -> Options -> Precision;
			}

			// Compile SASS using context provided
			int result = sass_compile(ctx);

			// Copy resulting fields from unmanaged structure to managed
			sassContext -> OutputString = gcnew String(ctx -> output_string);
			sassContext -> ErrorStatus = !!ctx -> error_status;
			sassContext -> ErrorMessage = gcnew String(ctx -> error_message);

			return result;
		}
		catch (exception& e)
		{
			throw gcnew Exception(gcnew String(e.what()));
		}
		catch (...)
		{
			throw gcnew Exception("Unhandled exception in native code");
		}
		finally
		{
			// Free resources
			FreeConstString(ctx -> options.source_map_file);
			FreeConstString(ctx -> options.source_map_root);
			FreeConstString(ctx -> options.include_paths);
			FreeConstString(ctx -> options.plugin_paths);
			FreeConstString(ctx -> options.indent);
			FreeConstString(ctx -> options.linefeed);
			// Any of the lines below leads to heap crash for unknown reasons. Commenting them may lead to memory leaks, but I haven't found better solution yet.
			//FreeConstString(ctx -> source_string);
			//FreeStringArray(ctx -> included_files, 0);
			//sass_free_context(ctx);
		}
	}

	int SassInterface::Compile(SassFileContext^ sassFileContext)
	{
		sass_file_context* ctx = sass_new_file_context();
		try
		{
			// Copy fields from managed structure to unmanaged
			ctx -> input_path = MarshalString(sassFileContext -> InputPath);
			if (sassFileContext -> Options)
			{
				ctx -> options.output_style = sassFileContext -> Options -> OutputStyle;
				ctx -> options.source_comments = sassFileContext -> Options -> SourceComments;
				ctx -> options.source_map_file = MarshalString(sassFileContext -> Options -> SourceMapFile);
				ctx -> options.omit_source_map_url = sassFileContext -> Options -> OmitSourceMapUrl;
				ctx -> options.source_map_embed = sassFileContext -> Options -> SourceMapEmbed;
				ctx -> options.source_map_contents = sassFileContext -> Options -> SourceMapContents;
				ctx -> options.source_map_root = MarshalString(sassFileContext -> Options -> SourceMapRoot);
				ctx -> options.is_indented_syntax_src = sassFileContext -> Options -> IsIndentedSyntaxSrc;
				ctx -> options.include_paths = MarshalString(sassFileContext -> Options -> IncludePaths);
				ctx -> options.plugin_paths = MarshalString(sassFileContext -> Options -> PluginPaths);
				ctx -> options.indent = MarshalString(sassFileContext -> Options -> Indent);
				ctx -> options.linefeed = MarshalString(sassFileContext -> Options -> Linefeed);
				ctx -> options.precision = sassFileContext -> Options -> Precision;
			}

			// Compile SASS using context provided
			int result = sass_compile_file(ctx);

			// Copy resulting fields from unmanaged structure to managed
			sassFileContext -> OutputString = gcnew String(ctx -> output_string);
			sassFileContext -> ErrorStatus = !!ctx -> error_status;
			sassFileContext -> ErrorMessage = gcnew String(ctx -> error_message);

			return result;
		}
		catch (exception& e)
		{
			throw gcnew Exception(gcnew String(e.what()));
		}
		catch (...)
		{
			throw gcnew Exception("Unhandled exception in native code");
		}
		finally
		{
			// Free resources
			FreeConstString(ctx -> options.source_map_file);
			FreeConstString(ctx -> options.source_map_root);
			FreeConstString(ctx -> options.include_paths);
			FreeConstString(ctx -> options.plugin_paths);
			FreeConstString(ctx -> options.indent);
			FreeConstString(ctx -> options.linefeed);
			FreeConstString(ctx -> input_path);
			sass_free_file_context(ctx);
		}
	}

	// Folder context isn't implemented in core libsass library now
	/*int SassInterface::Compile(SassFolderContext^ sassFolderContext)
	{
		sass_folder_context* ctx = sass_new_folder_context();
		try
		{
			// Copy fields from managed structure to unmanaged
			ctx -> search_path = MarshalString(sassFolderContext -> SearchPath);
			//ctx -> output_path = MarshalString(sassFolderContext -> OutputPath);
			if (sassFolderContext -> Options)
			{
				ctx -> options.output_style = sassFolderContext -> Options -> OutputStyle;
				ctx -> options.source_comments = sassFolderContext -> Options -> SourceComments;
				ctx -> options.source_map_file = MarshalString(sassFolderContext -> Options -> SourceMapFile);
				ctx -> options.omit_source_map_url = sassFolderContext -> Options -> OmitSourceMapUrl;
				ctx -> options.source_map_embed = sassFolderContext -> Options -> SourceMapEmbed;
				ctx -> options.source_map_contents = sassFolderContext -> Options -> SourceMapContents;
				ctx -> options.source_map_root = MarshalString(sassFolderContext -> Options -> SourceMapRoot);
				ctx -> options.is_indented_syntax_src = sassFolderContext -> Options -> IsIndentedSyntaxSrc;
				ctx -> options.include_paths = MarshalString(sassFolderContext -> Options -> IncludePaths);
				ctx -> options.plugin_paths = MarshalString(sassFolderContext -> Options -> PluginPaths);
				ctx -> options.indent = MarshalString(sassFolderContext -> Options -> Indent);
				ctx -> options.linefeed = MarshalString(sassFolderContext -> Options -> Linefeed);
				ctx -> options.precision = sassFolderContext -> Options -> Precision;
			}

			// Compile SASS using context provided
			int result = sass_compile_folder(ctx);

			// Copy resulting fields from unmanaged structure to managed
			//sassFolderContext -> OutputPath = gcnew String(ctx -> output_path);
			sassFolderContext -> ErrorStatus = !!ctx -> error_status;
			sassFolderContext -> ErrorMessage = gcnew String(ctx -> error_message);

			return result;
		}
		catch (exception& e)
		{
			throw gcnew Exception(gcnew String(e.what()));
		}
		catch (...)
		{
			throw gcnew Exception("Unhandled exception in native code");
		}
		finally
		{
			// Free resources
			FreeConstString(ctx -> options.source_map_file);
			FreeConstString(ctx -> options.source_map_root);
			FreeConstString(ctx -> options.include_paths);
			FreeConstString(ctx -> options.plugin_paths);
			FreeConstString(ctx -> options.indent);
			FreeConstString(ctx -> options.linefeed);
			FreeConstString(ctx -> search_path);
			sass_free_folder_context(ctx);
		}
	}*/
}