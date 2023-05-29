import Command.Base 1.0
import QtCharts
import QtQuick

ChartView {
    id: top

    title: "Progress"
    antialiasing: true

    LineSeries {
        id: xline

        name: "X"

        XYPoint {
            x: 0
            y: ProgressStatus.x.initialValue
        }

        XYPoint {
            x: 1
            y: ProgressStatus.x.firstValue
        }

        XYPoint {
            x: 2
            y: ProgressStatus.x.secondValue
        }

        XYPoint {
            x: 3
            y: ProgressStatus.x.thirdValue
        }

        XYPoint {
            x: 4
            y: ProgressStatus.x.forthValue
        }

        XYPoint {
            x: 5
            y: ProgressStatus.x.fifthValue
        }

        XYPoint {
            x: 6
            y: ProgressStatus.x.sixthValue
        }

        XYPoint {
            x: 7
            y: ProgressStatus.x.seventhValue
        }

        XYPoint {
            x: 8
            y: ProgressStatus.x.eighthValue
        }

        XYPoint {
            x: 9
            y: ProgressStatus.x.nighthValue
        }

        Connections {
            function onValuesChanged() {
                xline.removePoints(0, 10);
                xline.append(0, ProgressStatus.x.initialValue);
                xline.append(1, ProgressStatus.x.firstValue);
                xline.append(2, ProgressStatus.x.secondValue);
                xline.append(3, ProgressStatus.x.thirdValue);
                xline.append(4, ProgressStatus.x.forthValue);
                xline.append(5, ProgressStatus.x.fifthValue);
                xline.append(6, ProgressStatus.x.sixthValue);
                xline.append(7, ProgressStatus.x.seventhValue);
                xline.append(8, ProgressStatus.x.eighthValue);
                xline.append(9, ProgressStatus.x.nighthValue);
            }

            target: ProgressStatus.x
        }

    }

    LineSeries {
        id: yline

        name: "Y"

        XYPoint {
            x: 0
            y: ProgressStatus.y.initialValue
        }

        XYPoint {
            x: 1
            y: ProgressStatus.y.firstValue
        }

        XYPoint {
            x: 2
            y: ProgressStatus.y.secondValue
        }

        XYPoint {
            x: 3
            y: ProgressStatus.y.thirdValue
        }

        XYPoint {
            x: 4
            y: ProgressStatus.y.forthValue
        }

        XYPoint {
            x: 5
            y: ProgressStatus.y.fifthValue
        }

        XYPoint {
            x: 6
            y: ProgressStatus.y.sixthValue
        }

        XYPoint {
            x: 7
            y: ProgressStatus.y.seventhValue
        }

        XYPoint {
            x: 8
            y: ProgressStatus.y.eighthValue
        }

        XYPoint {
            x: 9
            y: ProgressStatus.y.nighthValue
        }

        Connections {
            function onValuesChanged() {
                yline.removePoints(0, 10);
                yline.append(0, ProgressStatus.y.initialValue);
                yline.append(1, ProgressStatus.y.firstValue);
                yline.append(2, ProgressStatus.y.secondValue);
                yline.append(3, ProgressStatus.y.thirdValue);
                yline.append(4, ProgressStatus.y.forthValue);
                yline.append(5, ProgressStatus.y.fifthValue);
                yline.append(6, ProgressStatus.y.sixthValue);
                yline.append(7, ProgressStatus.y.seventhValue);
                yline.append(8, ProgressStatus.y.eighthValue);
                yline.append(9, ProgressStatus.y.nighthValue);
            }

            target: ProgressStatus.y
        }

    }

    LineSeries {
        id: zline

        name: "Z"

        XYPoint {
            x: 0
            y: ProgressStatus.z.initialValue
        }

        XYPoint {
            x: 1
            y: ProgressStatus.z.firstValue
        }

        XYPoint {
            x: 2
            y: ProgressStatus.z.secondValue
        }

        XYPoint {
            x: 3
            y: ProgressStatus.z.thirdValue
        }

        XYPoint {
            x: 4
            y: ProgressStatus.z.forthValue
        }

        XYPoint {
            x: 5
            y: ProgressStatus.z.fifthValue
        }

        XYPoint {
            x: 6
            y: ProgressStatus.z.sixthValue
        }

        XYPoint {
            x: 7
            y: ProgressStatus.z.seventhValue
        }

        XYPoint {
            x: 8
            y: ProgressStatus.z.eighthValue
        }

        XYPoint {
            x: 9
            y: ProgressStatus.z.nighthValue
        }

        Connections {
            function onValuesChanged() {
                zline.removePoints(0, 10);
                zline.append(0, ProgressStatus.z.initialValue);
                zline.append(1, ProgressStatus.z.firstValue);
                zline.append(2, ProgressStatus.z.secondValue);
                zline.append(3, ProgressStatus.z.thirdValue);
                zline.append(4, ProgressStatus.z.forthValue);
                zline.append(5, ProgressStatus.z.fifthValue);
                zline.append(6, ProgressStatus.z.sixthValue);
                zline.append(7, ProgressStatus.z.seventhValue);
                zline.append(8, ProgressStatus.z.eighthValue);
                zline.append(9, ProgressStatus.z.nighthValue);
            }

            target: ProgressStatus.z
        }

    }

}
