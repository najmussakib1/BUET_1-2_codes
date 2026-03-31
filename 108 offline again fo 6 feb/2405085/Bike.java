class Bike extends Vehicle implements Serviceable {
    private int engineCapacity;
    private double serviceCost;
    private double maxServiceCost;

    Bike(String regNum, String ownerName, double baseServiceCost, int engineCapacity, double maxServiceCost) throws ServiceException {
        super(regNum, ownerName, baseServiceCost);
        this.engineCapacity = engineCapacity;
        this.maxServiceCost = maxServiceCost;
        if (maxServiceCost < 0) {
            throw new ServiceException("Max service cost cannot be negative");
        }
    }

    public double calculateServiceCost() throws ServiceException {
        serviceCost = getBaseServiceCost() + engineCapacity * 2;
        if (serviceCost > maxServiceCost) {
            serviceCost = maxServiceCost;
            throw new ServiceException("Service cost exceeds maximum limit for bike");
        }
        return serviceCost;
    }

    public void doService() {
        System.out.println("Servicing bike with engine capacity: " + engineCapacity);
        try {
            double sc = calculateServiceCost();
            System.out.println("Service completed. Cost: " + sc);
        } catch (ServiceException e) {
            System.out.println("Error servicing bike: " + e.getMessage());
        }
    }
}