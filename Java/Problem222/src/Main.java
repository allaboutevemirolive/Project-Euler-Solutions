public class Main {

    public static void main(String[] args) {
        System.out.println(new Main().run());
    }

    public String run() {
        sphereRadii = new double[21];
        for (int i = 0; i < sphereRadii.length; i++) {
            sphereRadii[i] = (i + 30) * 1000;
        }
        minLength = new double[sphereRadii.length][1 << sphereRadii.length];

        double min = Double.POSITIVE_INFINITY;
        for (int i = 0; i < sphereRadii.length; i++) {
            min = Math.min(findMinimumLength(i, (1 << sphereRadii.length) - 1) + sphereRadii[i], min);
        }
        return Long.toString(Math.round(min));
    }

    private double[] sphereRadii;

    private double[][] minLength;

    private double findMinimumLength(int currentSphereIndex, int setOfSpheres) {
        if ((setOfSpheres & (1 << currentSphereIndex)) == 0) {
            throw new IllegalArgumentException();
        }

        if (minLength[currentSphereIndex][setOfSpheres] == 0) {
            double result;
            if (Integer.bitCount(setOfSpheres) == 1) {
                result = sphereRadii[currentSphereIndex];
            } else {
                result = Double.POSITIVE_INFINITY;
                int newSetOfSpheres = setOfSpheres ^ (1 << currentSphereIndex);
                for (int i = 0; i < sphereRadii.length; i++) {
                    if ((newSetOfSpheres & (1 << i)) == 0) {
                        continue;
                    }
                    double temp = Math.sqrt((sphereRadii[i] + sphereRadii[currentSphereIndex] - 50000) * 200000);
                    temp += findMinimumLength(i, newSetOfSpheres);
                    result = Math.min(temp, result);
                }
            }
            minLength[currentSphereIndex][setOfSpheres] = result;
        }
        return minLength[currentSphereIndex][setOfSpheres];
    }
}
