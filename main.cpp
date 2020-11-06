#include "osgDB/Archive"
#include "osgDB/FileNameUtils"
#include "osgDB/Options"
#include "osgDB/ReadFile"
#include "osgDB/ReaderWriter"
#include "osgDB/Registry"
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

USE_OSGPLUGIN(png)
USE_OSGPLUGIN(zip)
USE_OSGPLUGIN(jpeg)
USE_OSGPLUGIN(rgb)
USE_OSGPLUGIN(OpenFlight)

int main(int, char **argv)
{
    std::filesystem::path GSModelZip = argv[1];
    osgDB::ReaderWriter *rw = osgDB::Registry::instance()->getReaderWriterForExtension("zip");
    if (rw) {
        // set relative path for GSModel
        osg::ref_ptr<osgDB::Options> options = new osgDB::Options();
        options->setDatabasePath(GSModelZip.parent_path());

        // read GSModel geometry
        osgDB::ReaderWriter::ReadResult GSModelRead = rw->openArchive(GSModelZip,
                                                                      osgDB::Archive::READ);
        if (GSModelRead.validArchive()) {
            osg::ref_ptr<osgDB::Archive> archive = GSModelRead.takeArchive();
            osgDB::Archive::FileNameList fileNameList;
            if (archive->getFileNames(fileNameList)) {
                for (osgDB::Archive::FileNameList::iterator itr = fileNameList.begin();
                     itr != fileNameList.end();
                     ++itr) {
                    auto result = archive->readObject(*itr, options.get());
                }
            }
        }
    }

    return 0;
}
