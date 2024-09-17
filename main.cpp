#include <QCoreApplication>
#include <QDirIterator>
#include <QImage>

#include <iostream>



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString path = "/home/zb_bamboo/Dokumente/2021";
    QString replacePath = "/home/zb_bamboo/Dokumente/";

/*
    // Dirs & Sub-Dirs
    QDirIterator it(path, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString dir = it.next();
        qDebug() << dir;
    }
*/

    std::cout << "\n#####\nFiles\n" << std::endl;
    // pics
    QDirIterator picsFileIt(path, {"*.jpg", "*.jpeg", "*.png", "*.bmp"}, QDir::Files, QDirIterator::Subdirectories);
    while (picsFileIt.hasNext()) {
        QFile f(picsFileIt.next());

        // path/to/file
        std::cout << "# " << f.fileName().toUtf8().toStdString() << std::endl;

        // filename
        QFileInfo fileInfo(f.fileName());
        std::cout << "## " << fileInfo.completeBaseName().toStdString() << " " << f.size() / 1024 << "Kb" << std::endl;

        // file extension
        std::cout << "## " << fileInfo.completeSuffix().toStdString() << std::endl;

        // only dir
        QDir d = QFileInfo(f).absoluteDir();
        std::cout << "### " << d.absolutePath().toStdString() << std::endl;

        // cutted dir
        QString fPath = d.absolutePath();
        fPath.remove(replacePath);
        std::cout << "#### " << fPath.toStdString() << std::endl;

        // create sub dir
        if(d.mkdir("web") == 0){
            std::cout << "#### " << "= dir created" << std::endl;

            // copy file w/o extension
            QFile::copy(f.fileName(), d.absolutePath() + "/web/" + fileInfo.completeBaseName());

            QString fImg = d.absolutePath() + "/web/" + fileInfo.completeBaseName();

            QImage image(fImg);

            std::cout << "img size: " << image.width() << "x" << image.height() << std::endl;

            // OK:: convert img to webp
            image.save(fImg + ".webp", "WEBP");
        }
    }

    //exit(0);

    exit(EXIT_SUCCESS);

}
