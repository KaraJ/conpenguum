TEMPLATE    = subdirs
SUBDIRS     =   \
    Comm      \
    Input	\
	Renderer \
	ResourceManager \
	Resources \
	UI \
	Update 


#I believe you can use something like this below to link to another part of the project, but I'm honestly not certain.
#contains(QT_CONFIG, opengl):SUBDIRS += opengl
# IE if we had say, Utility folder in the client folder, we could have something like
# contains(QT_CONFIG, utility):SUBDIRS += utility
# and that would include itself...unfortunately the project files are somewhat undocumented.
