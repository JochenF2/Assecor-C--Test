#pragma once

namespace MyAssecorLibrary
{
	enum class AddResult
	{
		eOk = 0,
		eDuplicatedID,
		eNoRepositoryFound,
		eUnknownError,
		eCount
	};

	enum class GetResult
	{
		eOk = 0,
		eIDNotFound,
		eNoRepositoryFound,
		eUnknownError,
		eCount
	};


	enum class CreateRepositoryResult
	{
		eOk,
		eFileHandlingError,
		/*
		more possible Errors for creating a repository in e.g. a file, cloud, ...
		*/
		eUnknown
	};

}
