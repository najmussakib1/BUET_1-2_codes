abstract class Vehicle {
    private String regNum;
    private String ownerName;
    private double baseServiceCost;

    Vehicle(String regNum, String ownerName, double baseServiceCost) throws ServiceException {
        if (regNum == null || regNum.isEmpty()) {
            throw new ServiceException("Registration number cannot be empty");
        }
        if (ownerName == null || ownerName.isEmpty()) {
            throw new ServiceException("Owner name cannot be empty");
        }
        if (baseServiceCost < 0) {
            throw new ServiceException("Base service cost cannot be negative");
        }
        this.regNum = regNum;
        this.ownerName = ownerName;
        this.baseServiceCost = baseServiceCost;
    }

    public String getRegNum() {
        return regNum;
    }

    public String getOwnerName() {
        return ownerName;
    }

    public double getBaseServiceCost() {
        return baseServiceCost;
    }

    public abstract double calculateServiceCost() throws ServiceException;

    void displayDetails() {
        System.out.println("Registration Number: " + regNum);
        System.out.println("Owner Name: " + ownerName);
        System.out.println("Base Service Cost: " + baseServiceCost);
    }
}