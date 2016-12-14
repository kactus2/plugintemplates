// Copyright Tampere University of Technology
//-----------------------------------------------------------------------------
// File: tst_SampleGenerator.cpp
//-----------------------------------------------------------------------------
// Project: Kactus2
// Author: Janne Virtanen
// Date: 14.12.2016
//
// Description:
// Unit test for class SampleGenerator.
//-----------------------------------------------------------------------------

#include <QtTest>

#include <tests/MockObjects/LibraryMock.h>

#include <IPXACTmodels/Component/Component.h>
#include <IPXACTmodels/Design/Design.h>
#include <IPXACTmodels/Design/ComponentInstance.h>

#include <Plugins/SampleGenerator/SampleParser.h>
#include <Plugins/SampleGenerator/SampleGenerator.h>

class tst_SampleGenerator : public QObject
{
    Q_OBJECT

public:
    tst_SampleGenerator();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    // Test cases:
    void singleInstance();
    void multipleInstances();
    void testGeneration();
    void testGeneration_data();

    // Convenience functions to re-create elements commonly used in test cases.
    QSharedPointer<Component> createComponent(VLNV componentVLNV);
    QSharedPointer<FileSet> createFileSet(QString fileSetName, QSharedPointer<Component> testComponent);
    QSharedPointer<ComponentInstance> createInstance(QString instanceName, VLNV componentVLNV);

    // Read and verify an output file.
    void readOutputFile();
    void compareOutputTo(QString const& expectedOutput);
    void verifyOutputContains(QString const& expectedOutput);

private:

    //! The top level component for which the generator is run.
    QSharedPointer<Component> topComponent_;

    //! The design for which the generator is run.
    QSharedPointer<Design> design_;

    //! The view of the top component chosen as the active view.
    QSharedPointer<View> topView_;

    //! The test mock for library interface.
    LibraryMock library_;

    //! Will contain the generator output.
    QString output_;
};

//-----------------------------------------------------------------------------
// Function: tst_SampleGenerator::tst_SampleGenerator()
//-----------------------------------------------------------------------------
tst_SampleGenerator::tst_SampleGenerator(): topComponent_(), design_(), library_(this), output_()
{
}

//-----------------------------------------------------------------------------
// Function: tst_SampleGenerator::initTestCase()
//-----------------------------------------------------------------------------
void tst_SampleGenerator::initTestCase()
{
}

//-----------------------------------------------------------------------------
// Function: tst_SampleGenerator::cleanupTestCase()
//-----------------------------------------------------------------------------
void tst_SampleGenerator::cleanupTestCase()
{
}

//-----------------------------------------------------------------------------
// Function: tst_SampleGenerator::init()
//-----------------------------------------------------------------------------
void tst_SampleGenerator::init()
{
    VLNV vlnv(VLNV::COMPONENT, "Test", "TestLibrary", "TestComponent", "1.0");
    topComponent_ = QSharedPointer<Component>(new Component(vlnv));

    VLNV designVlnv(VLNV::DESIGN, "Test", "TestLibrary", "TestDesign", "1.0");
    design_ = QSharedPointer<Design>(new Design(designVlnv));

    topView_ = QSharedPointer<View>(new View("topView"));

    topComponent_->getViews()->append(topView_);

    library_.clear();
}

//-----------------------------------------------------------------------------
// Function: tst_SampleGenerator::cleanup()
//-----------------------------------------------------------------------------
void tst_SampleGenerator::cleanup()
{
    topComponent_.clear();
    design_.clear();
    topView_.clear();

    output_.clear();

    QFile::remove("./sampleGeneratedFile.v");
}

//-----------------------------------------------------------------------------
// Function: tst_SampleGenerator::createComponent()
//-----------------------------------------------------------------------------
QSharedPointer<Component> tst_SampleGenerator::createComponent(VLNV componentVLNV)
{
    QSharedPointer<Component> testComponent = QSharedPointer<Component>(new Component(componentVLNV));
    library_.addComponent(testComponent);
    return testComponent;
}

//-----------------------------------------------------------------------------
// Function: tst_SampleGenerator::createInstance()
//-----------------------------------------------------------------------------
QSharedPointer<ComponentInstance> tst_SampleGenerator::createInstance(QString instanceName, VLNV componentVLNV)
{
    QSharedPointer<ConfigurableVLNVReference> refVLNV (new ConfigurableVLNVReference(componentVLNV));
    QSharedPointer<ComponentInstance> testInstance(new ComponentInstance(instanceName, refVLNV));
    design_->getComponentInstances()->append(testInstance);
    return testInstance;
}

//-----------------------------------------------------------------------------
// Function: tst_SampleGenerator::createFileSet()
//-----------------------------------------------------------------------------
QSharedPointer<FileSet> tst_SampleGenerator::createFileSet(QString fileSetName, QSharedPointer<Component> testComponent)
{
    QSharedPointer<FileSet> testFileSet(new FileSet);
    QSharedPointer<File> testFile(new File);
    testFileSet->setName(fileSetName);
    testFileSet->getFiles()->append(testFile);
    testComponent->getFileSets()->append(testFileSet);

    return testFileSet;
}

//-----------------------------------------------------------------------------
// Function: tst_SampleGenerator::readOutputFile()
//-----------------------------------------------------------------------------
void tst_SampleGenerator::readOutputFile()
{
    QFile outputFile("./sampleGeneratedFile.txt");

    QVERIFY(outputFile.open(QIODevice::ReadOnly));

    output_ = outputFile.readAll();
    outputFile.close();
}

//-----------------------------------------------------------------------------
// Function: tst_SampleGenerator::compareLineByLine()
//-----------------------------------------------------------------------------
void tst_SampleGenerator::compareOutputTo(QString const& expectedOutput)
{
    readOutputFile();

    QCOMPARE(output_, expectedOutput);
}

//-----------------------------------------------------------------------------
// Function: tst_SampleGenerator::verifyOutputContains()
//-----------------------------------------------------------------------------
void tst_SampleGenerator::verifyOutputContains(QString const& expectedOutput)
{
    readOutputFile();

    if (!output_.contains(expectedOutput))
    {
        QStringList outputLines = output_.split("\n");
        QStringList expectedLines = expectedOutput.split("\n");

        QVERIFY(outputLines.count() >= expectedLines.count());

        int lineOffset = outputLines.indexOf(expectedLines.first());

        if (lineOffset == -1)
        {
            compareOutputTo(expectedOutput);
        }
        else
        {
            int lineCount = expectedLines.count();
            for (int i = 0; i < lineCount; i++)
            {
                QCOMPARE(outputLines.at(i + lineOffset), expectedLines.at(i));
            }
        }
    }
    else if(output_.count(expectedOutput) != 1)
    {
        QVERIFY2(false, QString(expectedOutput + " was found " + QString::number(output_.count(expectedOutput))
            + " times in output.").toLocal8Bit());
    }
}

//-----------------------------------------------------------------------------
// Function: tst_SampleGenerator::singleInstance()
//-----------------------------------------------------------------------------
void tst_SampleGenerator::singleInstance()
{
    VLNV componentVLNV(VLNV::COMPONENT, "Test", "TestLibrary", "TestComponent", "1.0");
    QSharedPointer<Component> testComponent = createComponent(componentVLNV);

    QSharedPointer<FileSet> testFileSet = createFileSet("testFileSet1",testComponent);

    QSharedPointer<ComponentInstance> testInstance = createInstance("testInstance",componentVLNV);

    SampleParser sparser;
    sparser.parse(&library_,design_);

    QCOMPARE(sparser.getParsedData()->size(), 1);
    QCOMPARE(sparser.getParsedData()->first()->fileSet, testFileSet);
}

//-----------------------------------------------------------------------------
// Function: tst_SampleGenerator::multipleInstances()
//-----------------------------------------------------------------------------
void tst_SampleGenerator::multipleInstances()
{
    VLNV componentVLNV1(VLNV::COMPONENT, "Test", "TestLibrary", "TestComponent1", "1.0");
    VLNV componentVLNV2(VLNV::COMPONENT, "Test", "TestLibrary", "TestComponent2", "1.0");
    QSharedPointer<Component> testComponent1 = createComponent(componentVLNV1);
    QSharedPointer<Component> testComponent2 = createComponent(componentVLNV2);

    QSharedPointer<FileSet> testFileSet1 = createFileSet("testFileSet1",testComponent1);
    QSharedPointer<FileSet> testFileSet2 = createFileSet("testFileSet2",testComponent2);
    QSharedPointer<FileSet> testFileSet3 = createFileSet("testFileSet3",testComponent2);

    QSharedPointer<ComponentInstance> testInstance1 = createInstance("testInstance1",componentVLNV1);
    QSharedPointer<ComponentInstance> testInstance2 = createInstance("testInstance2",componentVLNV2);
    QSharedPointer<ComponentInstance> testInstance3 = createInstance("testInstance3",componentVLNV1);

    SampleParser sparser;
    sparser.parse(&library_,design_);

    QCOMPARE(sparser.getParsedData()->size(), 4);
    QCOMPARE(sparser.getParsedData()->at(0)->fileSet, testFileSet1);
    QCOMPARE(sparser.getParsedData()->at(1)->fileSet, testFileSet2);
    QCOMPARE(sparser.getParsedData()->at(2)->fileSet, testFileSet3);
    QCOMPARE(sparser.getParsedData()->at(3)->fileSet, testFileSet1);
}

//-----------------------------------------------------------------------------
// Function: tst_SampleGenerator::testGeneration()
//-----------------------------------------------------------------------------
void tst_SampleGenerator::testGeneration()
{
    QFETCH(QString, fileSetName);

    QSharedPointer<QList<QSharedPointer<SampleParser::SampleData> > > datas
        (new QList<QSharedPointer<SampleParser::SampleData> >);
    QSharedPointer<FileSet> testFileSet(new FileSet);
    testFileSet->setName(fileSetName);
    QSharedPointer<SampleParser::SampleData> sdata(new SampleParser::SampleData);
    sdata->fileSet = testFileSet;
    datas->append(sdata);

    SampleGenerator sgenerator(datas);
    sgenerator.generate(topComponent_, ".");

    verifyOutputContains(fileSetName);
}

//-----------------------------------------------------------------------------
// Function: tst_SampleGenerator::testGeneration_data()
//-----------------------------------------------------------------------------
void tst_SampleGenerator::testGeneration_data()
{
    QTest::addColumn<QString>("fileSetName");

    QTest::newRow("First") << "first";
    QTest::newRow("Last") << "last";
}

QTEST_APPLESS_MAIN(tst_SampleGenerator)

#include "tst_SampleGenerator.moc"
