#include <iostream>
#include "OpenGL_Debug.h"

namespace opengl{
	namespace debug{

		////////////////////////////////////////////////////////////////////////
		///
		/// @fn std::string ObtenirProgrammeLog(GLuint handle)
		///
		/// Permet de récupérer les messages d'erreurs provenant de OpenGL pour
		/// les programmes et les nuanceurs.
		///
		/// @return Une chaine de caractère contenant les messages d'erreurs.
		///
		////////////////////////////////////////////////////////////////////////
		std::string ObtenirProgrammeLog(GLuint handle)
		{
			std::string log;
			GLint infologLength{ 0 };
			glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &infologLength);
			if (infologLength > 1)
			{
				std::cerr << "Erreur(s)" << '\n';
				char* infoLog{ new char[infologLength + 1] };
				int charsWritten{ 0 };
				glGetProgramInfoLog(handle, infologLength, &charsWritten, infoLog);
				log = infoLog;
				delete [] infoLog;
			}
			return log;
		}
	}
}