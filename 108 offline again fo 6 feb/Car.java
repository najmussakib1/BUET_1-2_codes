class Car extends Vehicle implements Serviceable {
    private int numOfDoor;
    private double serviceCost;
    private double maxServiceCost;

    Car(String regNum, String ownerName, double baseServiceCost, int numOfDoor, double maxServiceCost) throws ServiceException {
        super(regNum, ownerName, baseServiceCost);
        this.numOfDoor = numOfDoor;
        this.maxServiceCost = maxServiceCost;
        if (maxServiceCost < 0) {
            throw new ServiceException("Max service cost cannot be negative");
        }
    }

    public double calculateServiceCost() throws ServiceException {
        serviceCost = getBaseServiceCost() + numOfDoor * 500;
        if (serviceCost > maxServiceCost) {
            serviceCost = maxServiceCost;
            throw new ServiceException("Service cost exceeds maximum limit for car");
        }
        return serviceCost;
    }

    public void doService() {
        System.out.println("Servicing car with number of doors: " + numOfDoor);
        try {
            double sc = calculateServiceCost();
            System.out.println("Service completed. Cost: " + sc);
        } catch (ServiceException e) {
             System.out.println("Error servicing car: " + e.getMessage());
        }
    }
}