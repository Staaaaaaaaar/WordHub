/****************************************************************************
** Meta object code from reading C++ file 'guess_word_widget.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../guess_word_widget.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'guess_word_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN17guess_word_widgetE_t {};
} // unnamed namespace

template <> constexpr inline auto guess_word_widget::qt_create_metaobjectdata<qt_meta_tag_ZN17guess_word_widgetE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "guess_word_widget",
        "exitRequested",
        "",
        "ruleRequested",
        "beginRequested",
        "answerRequested",
        "commitRequested"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'exitRequested'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'ruleRequested'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'beginRequested'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'answerRequested'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'commitRequested'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<guess_word_widget, qt_meta_tag_ZN17guess_word_widgetE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject guess_word_widget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17guess_word_widgetE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17guess_word_widgetE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN17guess_word_widgetE_t>.metaTypes,
    nullptr
} };

void guess_word_widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<guess_word_widget *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->exitRequested(); break;
        case 1: _t->ruleRequested(); break;
        case 2: _t->beginRequested(); break;
        case 3: _t->answerRequested(); break;
        case 4: _t->commitRequested(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (guess_word_widget::*)()>(_a, &guess_word_widget::exitRequested, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (guess_word_widget::*)()>(_a, &guess_word_widget::ruleRequested, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (guess_word_widget::*)()>(_a, &guess_word_widget::beginRequested, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (guess_word_widget::*)()>(_a, &guess_word_widget::answerRequested, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (guess_word_widget::*)()>(_a, &guess_word_widget::commitRequested, 4))
            return;
    }
}

const QMetaObject *guess_word_widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *guess_word_widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN17guess_word_widgetE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int guess_word_widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void guess_word_widget::exitRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void guess_word_widget::ruleRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void guess_word_widget::beginRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void guess_word_widget::answerRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void guess_word_widget::commitRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
