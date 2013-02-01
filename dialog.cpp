 #include <QDialog>

 class QLabel;
 class QPushButton;
 class QTextEdit;
 class QLineEdit;

 class dialog : public QDialog
 {
 public:
     AddDialog(QWidget *parent=0);
     QLineEdit *fileName;

 private:
     QLabel *nameLabel;
     QPushButton *okButton;
     QPushButton *cancelButton;
 };
